#ifndef _WR_H_
#define _WR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/signal.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#define MAXLINE 1023
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
ssize_t readn(int fd, void *buf, size_t count);
ssize_t writen(int fd, const void *buf, size_t count);
ssize_t recv_peek(int sockfd, void *buf, size_t len);
ssize_t readline(int sockfd, void *buf, size_t maxline);
#endif
