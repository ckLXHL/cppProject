#ifndef RIO_H
#define RIO_H 

#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "NonCopyable.h"
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
class RIO : private NonCopyable{
	public:
		RIO(int);
		ssize_t readn(int len);
		ssize_t recv_peek(int len);
		ssize_t writen(int len);
		ssize_t readline(int len);
		void copy_buf(char*);
		char *get_buf();
	private:
		int fd_;
		char buf_[8192];
};
#endif  /*RIO_H*/
