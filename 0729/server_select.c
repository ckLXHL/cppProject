#include "WR.h" 
int server_init() {
	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
		ERR_EXIT("socket");
	int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on))
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
	if (ret < 0)
		ERR_EXIT("listen");
	return listenfd;
}
int main(int argc, const char *argv[])
{
	signal(SIGPIPE, SIG_IGN);
	int listenfd = server_init();
	int i;
	int client[FD_SETSIZE];
	for ( i = 0; i < FD_SETSIZE; i++) {
		client[i] = -1;
	}
	int maxi = 0;
	int maxfd = listenfd;
	int nready;
	fd_set allset, rset;
	FD_ZERO(&allset);
	FD_ZERO(&rset);
	FD_SET(listenfd, &allset);
	while (1) {
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (nready == -1) {
			if (errno == EINTR)
				continue;
			else
				ERR_EXIT("select");
		}
		if (nready == 0) 
			continue;
		if (FD_ISSET(listenfd, &rset)) {
			struct sockaddr_in peeraddr;
			bzero(&peeraddr, sizeof peeraddr);
			len = sizeof peeraddr;
			//accept
			int peerfd = accept(listenfd, (struct sockaddr*)&peeraddr,&len);
			if (peerfd == -1) 
				ERR_EXIT("accept");
			int i;
			for (i = 0; i < FD_SETSIZE; i++) {
				if (client[i] == -1) {
					client[i] =peerfd;
					if (i > maxi) {
						maxi = i;
					}
					break;
				}
			}
			//too many
			if (i == FD_SETSIZE) {
				puts("too many clients");
				exit(EXIT_FAILURE);
			}
			//add to allset
			FD_SET(peerfd, &allset);
			if (peerfd > maxfd) {
				maxfd = peerfd;
			}
			printf("IP = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));
			if(--nready <= 0) 
				continue;
		}
		int i;
		for (i = 0; i <= maxi; i++) {
			int peerfd = client[i];
			if (peerfd == -1) 
				continue;
			if (FD_ISSET(peerfd, &rset)) {
				char recvbuf[MAXLINE + 1] = {0};
				int ret = readline(peerfd, recvbuf, MAXLINE);
				if (ret == -1)
					ERR_EXIT("readline");
				if (ret == 0) {
					puts("client close");
					FD_CLR(peerfd, &allset);
					client[i] = -1;
					close(peerfd);
					continue;
				}
				printf("receive: %s\n",recvbuf);
				writen(peerfd, recvbuf, strlen(recvbuf));
				if (--nready <= 0)
					break;
			}
		}
	}
	close(listenfd);
	return 0;
}
