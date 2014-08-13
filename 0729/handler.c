#include "handler.h"
void do_client_select(int fd) {
	char recvbuf[MAXLINE + 1];
	char sendbuf[MAXLINE + 1];
	memset(recvbuf, 0x00, sizeof recvbuf);
	memset(sendbuf, 0x00, sizeof sendbuf);

	fd_set rset;
	int maxfd;
	int nready;
	int stdin_fd = fileno(stdin);
	maxfd = (stdin_fd > fd) ? stdin_fd : fd;
	FD_ZERO(&rset);
	int stdin_eof = 0;

	while (1) {
		if (stdin_eof == 0) {
			FD_SET(stdin_fd, &rset);
		}
		FD_SET(fd, &rset);
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (nready < 0) {
			ERR_EXIT("select");
		}
		if (nready == 0) {
			continue;
		}
		if (FD_ISSET(stdin_fd, &rset)) {
			if (fgets(sendbuf, MAXLINE, stdin) == NULL) {
				//break;
				/*close(fd);
				  sleep(4);
				  exit(EXIT_FAILURE); */
				stdin_eof = 1; //停止监听该描述符
				shutdown(fd, SHUT_WR);

			} else {
				if(strcmp(sendbuf, "\n") == 0){
					continue;
				}
				writen(fd, sendbuf, strlen(sendbuf));
				memset(sendbuf, 0x00, sizeof sendbuf);
			}
		}
		if (FD_ISSET(fd, &rset)) {
			int ret = readline(fd, recvbuf, MAXLINE);
			if (ret == -1) {
				ERR_EXIT("readline");
			}
			if (ret == 0) {
				fputs("server close\n", stdout);
				break;
			}
			fprintf(stdout, "receive: %s", recvbuf);
			memset(recvbuf, 0x00, sizeof recvbuf);
		}
	}
}
void do_client_poll(int fd) {
	char recvbuf[MAXLINE + 1];
	char sendbuf[MAXLINE + 1];
	memset(recvbuf, 0x00, sizeof recvbuf);
	memset(sendbuf, 0x00, sizeof sendbuf);

	int maxi = 0;	//最大可用的下标
	struct pollfd client[2];
	int nready;
	client[0].fd = fd;
	client[0].events = POLLIN;
	int stdin_fd = fileno(stdin);
	client[1].fd = stdin_fd;
	client[1].events = POLLIN;
	maxi = 1;

	while (1) {
		nready = poll(client, maxi + 1, -1);
		if (nready < 0) {
			if (errno == EINTR) {
				continue;
			}
			ERR_EXIT("poll");
		}
		if (nready == 0) {
			continue;
		}

		//if (FD_ISSET(stdin_fd, &rset)) {
		if (client[1].revents & POLLIN) {
			if (fgets(sendbuf, MAXLINE, stdin) == NULL) {
				//break;
				//stdin_eof = 1; //停止监听该描述符
				client[1].fd = -1; //停止监听
				shutdown(fd, SHUT_WR);

			} else {
				if (strcmp(sendbuf, "\n") == 0) {
					continue;
				}
				writen(fd, sendbuf, strlen(sendbuf));
				memset(sendbuf, 0x00, sizeof sendbuf);
			}
		}
		//if (FD_ISSET(fd, &rset)) {
		if (client[0].revents & POLLIN) {
			int ret = readline(fd, recvbuf, MAXLINE);
			if (ret == -1) {
				ERR_EXIT("readline");
			}
			if (ret == 0) {
				fputs("server close\n", stdout);
				client[0].fd = -1;
				break;
			}
			fprintf(stdout, "receive: %s", recvbuf);
			memset(recvbuf, 0x00, sizeof recvbuf);
		}
	}
}
void do_client_epoll(int fd) {
	char recvbuf[MAXLINE + 1];
	char sendbuf[MAXLINE + 1];
	memset(recvbuf, 0x00, sizeof recvbuf);
	memset(sendbuf, 0x00, sizeof sendbuf);

	int epollfd = epoll_create(2);
	if (epollfd == -1) {
		ERR_EXIT("epoll_create");
	}
	struct epoll_event events[2];
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
	if (ret == -1) {
		ERR_EXIT("epoll_ctl");
	}
	int stdin_fd = fileno(stdin);
	ev.data.fd = stdin_fd;
	ev.events = EPOLLIN;
	ret = epoll_ctl(epollfd, EPOLL_CTL_ADD, stdin_fd, &ev);
	if (ret == -1) {
		ERR_EXIT("epoll_ctl");
	}
	int nready;

	while (1) {

		//nready = poll(client, maxi + 1, -1);
		nready = epoll_wait(epollfd, events, 2, -1);
		if (nready < 0) {
			if (errno == EINTR) {
				continue;
			}
			ERR_EXIT("epoll_wait");
		}
		if (nready == 0) {
			continue;
		}

		int i;
		for (i = 0; i < nready; ++i) {

			//if (client[1].revents & POLLIN) {
			if (events[i].data.fd == stdin_fd) {

				if (fgets(sendbuf, MAXLINE, stdin) == NULL) {
					//break;
					//stdin_eof = 1; //停止监听该描述符
					//client[1].fd = -1; //停止监听
					ev.data.fd = stdin_fd;
					epoll_ctl(epollfd, EPOLL_CTL_DEL, stdin_fd, &ev); //从events中删除该fd
					shutdown(fd, SHUT_WR);

				} else {
					if (strcmp(sendbuf, "\n") == 0) {
						continue;
					}
					writen(fd, sendbuf, strlen(sendbuf));
					memset(sendbuf, 0x00, sizeof sendbuf);
				}
			}

			//if (client[0].revents & POLLIN) {
			if(events[i].data.fd == fd){
				int ret = readline(fd, recvbuf, MAXLINE);
				if (ret == -1) {
					ERR_EXIT("readline");
				}
				if (ret == 0) {
					fputs("server close\n", stdout);
					//client[0].fd = -1;
					ev.data.fd = fd;
					epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &ev); //delete
					close(epollfd);
					exit(EXIT_SUCCESS);	//直接退出程序
				}
				fprintf(stdout, "receive: %s", recvbuf);
				memset(recvbuf, 0x00, sizeof recvbuf);
			}

		}
	}

}
void do_server_select(int fd);
void do_server_poll(int fd);
void do_server_epoll(int fd);
int server_init();
int client_init();
