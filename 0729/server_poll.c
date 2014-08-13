#include "WR.h"
int main(int argc, const char *argv[])
{
	signal(SIGPIPE, SIG_IGN);
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd == -1)
		ERR_EXIT("socket");
	int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) < 0)
		ERR_EXIT("setsockopt");
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(8989);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	socklen_t len = sizeof servaddr;
	int ret = bind(listenfd, (struct sockaddr*)&servaddr, len);
	if (ret < 0)
		ERR_EXIT("bind");
	ret = listen(listenfd, SOMAXCONN);
	if(ret < 0)
		ERR_EXIT("listen");
	struct pollfd client[2048];
	int i;
	for (i = 0; i < 2048; ++i) 
		client[i].fd = -1;
	client[0].fd = listenfd;
	client[0].events = POLLIN;
	int maxi = 0;
	int nready;
	while (1) {
		nready = poll(client, maxi + 1, -1);
		if (nready == -1) {
			if(errno == EINTR) 
				continue;
			else
				ERR_EXIT("poll");
		}
		if (nready == 0)
			continue;
		if(client[0].revents & POLLIN) {
			struct sockaddr_in peeraddr;
			bzero(&peeraddr, sizeof peeraddr);
			len = sizeof peeraddr;
			int peerfd = accept(listenfd, (struct sockaddr*)&peeraddr, &len);
			if (peerfd == -1)
				ERR_EXIT("accept");
			int i;
			for (i = 0; i < 2048; i++) {
				if(client[i].fd == -1) {
					client[i].fd = peerfd;
					client[i].events = POLLIN;
					if (i > maxi)
						maxi = i;
					break;
				}
			}
			if (i == 2048) {
				puts( "too many clients");
				exit(EXIT_FAILURE);
			}
			printf("IP = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			//如果等于零，其他fd不需要操作
			if(--nready <= 0)
				continue;
		}
		int i;
		for (i = 1; i <= maxi; ++i) {
			int peerfd = client[i].fd;
			if (peerfd == -1)
				continue;
			if(client[i].revents & POLLIN) {
				char recvbuf[MAXLINE + 1] = {0};
				int ret = readline(peerfd, recvbuf, MAXLINE);
				if(ret == -1)
					ERR_EXIT("readline");
				if(ret == 0) {
					puts("client close");
					close(peerfd);
					client[i].fd = -1;
					continue;
				}
				printf("recv: %s\n", recvbuf);
				writen(peerfd, recvbuf, strlen(recvbuf));
				if(--nready <= 0)
					break;
			}
		}
	}
	close(listenfd);
	return 0;
}
