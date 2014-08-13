#include "WR.h"
#define EVENT_MAX 100
int server_init(){
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		ERR_EXIT("socket");
	int on = 1;
	if (setsockopt(listenfd,SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) < 0)
		ERR_EXIT("setsockopt");
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8989);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len = sizeof servaddr;
	int ret = bind(listenfd, (struct sockaddr*)&servaddr, len);
	if(ret < 0) 
		ERR_EXIT("bind");
	ret = listen(listenfd, SOMAXCONN);
	if(ret < 0)
		ERR_EXIT("listen");
	return listenfd;
}
typedef struct epoll_tag {
	int listenfd_;
	int epollfd_;
	struct epoll_event events_[EVENT_MAX];
	int nready_;
}epoll_t;

void epoll_init(epoll_t *ep, int listenfd) {
	if ((ep->epollfd_ = epoll_create(EVENT_MAX)) == -1)
		ERR_EXIT("epoll_create");
	struct epoll_event ev;
	ep->listenfd_ = listenfd;
	ev.data.fd = listenfd;
	ev.events = EPOLLIN;
	if ((epoll_ctl(ep->epollfd_, EPOLL_CTL_ADD, listenfd, &ev)) == -1)
		ERR_EXIT("epoll_ctl_add");
}
void epoll_handle_wait(epoll_t *ep) {
		ep->nready_ = epoll_wait(ep->epollfd_, ep->events_, EVENT_MAX, -1);
		if (ep->nready_ == -1) {
			if(errno == EINTR)
				return;
			else
				ERR_EXIT("epoll");
		}
		if (ep->nready_ == 0) 
			return;
}
void epoll_handle_listen(epoll_t *ep) {
	struct sockaddr_in peeraddr;
	socklen_t len = sizeof peeraddr;
	bzero(&peeraddr, sizeof peeraddr);
	int connfd = accept(ep->listenfd_, (struct sockaddr*)&peeraddr, &len);
	if(connfd == -1)
		ERR_EXIT("accept");
	struct epoll_event ev;
	ev.data.fd = connfd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(ep->epollfd_, EPOLL_CTL_ADD, connfd, &ev);
	if (ret == -1)
		ERR_EXIT("epoll add");
	printf("IP = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
}
void epoll_handle_date(epoll_t *ep, int i) {
	int peerfd = ep->events_[i].data.fd;
	if (peerfd == -1)
		return;
	if (ep->events_[i].events & POLLIN) {
		char recvbuf[MAXLINE + 1] = {0};
		int ret = readline(peerfd, recvbuf, MAXLINE);
		if (ret == -1)
			ERR_EXIT("readline");
		if (ret == 0) {
			printf("client close\n");
			struct epoll_event ev;
			ev.data.fd = peerfd;
			ret = epoll_ctl(ep->epollfd_, EPOLL_CTL_DEL, peerfd, &ev);
			if(ret == -1)
				ERR_EXIT("epoll_ctl");
			close(peerfd);
			return;
		}
		printf("receive:%s", recvbuf);
		writen(peerfd, recvbuf,strlen(recvbuf));
	}

}
void do_epoll_server(int listenfd) {
	epoll_t ep;
	epoll_init(&ep, listenfd);
	int ret;
	while (1) {
		epoll_handle_wait(&ep);
		int i;
		for (i = 0; i < ep.nready_; i++) {
			if(ep.events_[i].data.fd == listenfd) {
				epoll_handle_listen(&ep);
			} else {
				epoll_handle_date(&ep, i);
			}
		}
	}

}
int main(int argc, const char *argv[])
{
	signal(SIGPIPE, SIG_IGN);
	int fd = server_init();
	do_epoll_server(fd);
	close(fd);
	return 0;
}
