#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#define RIO_BUFFER = 8192
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
typedef struct {
	int fd_;  //要读取的fd
	int left_;    //代表缓冲区剩余的字节数
	char *bufptr_;   //缓冲区有效数据的起始位置
	char buffer_[RIO_BUFFER]; //缓冲区
} rio_t;
void rio_init(rio_t *ri, int fd) {
	ri->fd_ = fd;
	ri->left_ = 0;
	bufptr_ = buffer_;
}
ssize_t rio_read(rio_t *ri, char *usrbuf, size_t len) {
	
	while(ri->left_ <= 0) {
		memset(buffer_, 0, sizeof(buffer_));
		ri->left_ = read(ri->fd_, ri->buffer_, RIO_BUFFER);	
		if(ri->left_ == -1){
			if(errno == EINTR)
				continue;
			return -1;
		}else if(ri->left_ == 0)
			return 0;
		bufptr_ = buffer_;
	}
	int ret = len > re->left_ ? re->left_ : len;
	memcpy(usrbuf, ri->bufptr_, ret);
	ri->bufptr_ += ret;
	ri->left_ -= ret;
	return ret;
}
ssize_t rio_readn(rio_t *ri, char *usrbuf, size_t len) {
	size_t left = len;
	char *bufp = usrbuf;
	ssize_t readn;
	while(left > 0) {
		if(readn = rio_read(ri, bufp, len) == -1)
			return -1;
		else if(readn == 0)
			break;
		bufp += readn;
		left -= readn;
	}
	return (len - left);
}
ssize_t rio_readline(rio_t *ri, char *usrbuf, size_t max_len) {
	char *bufp = usrbuf;
	ssize_t readn;
	char c;
	int i = ;
	for(i = 0; i < max_len - 1; i++) {
		if(readn = rio_read(ri, &c, 1) == -1)
			return -1;
		else if(readn == 0){
			if(i == 0)
				return 0;
			break;
		}
		*bufp++ = c;
		if(c == '\n')
			break;
	}
	*bufp = 0;
	return i;
}
ssize_t readn(int fd, char *buf, size_t n) {
	char* buf_n = buf;
	size_t left = n;
	ssize_t readn;
	while(left > 0) {
		if((readn = read(fd, buf_n, n)) == -1){
			if(errno == EINTR) 
				readn = 0;
			else
				return -1;
		}else if(readn == 0) 
			break;
		left -= readn;
		buf_n += readn;
	}
	return (n - left);
}
ssize_t writen(int fd, char *buf, size_t n) {
	char *buf_n = buf;
	size_t left = n;
	ssize_t writen;
	while(left > 0) {
		if((writen = write(fd, buf_n, left)) <= 0) {
			if(errno == EINTR) 
				continue;
			else
				return -1;
		}
		left -= writen;
		buf_n += writen;
	}
	return n;
}
int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		ERR_EXIT("open");
	char buf[1024] = {0};
	int flag;
	while((flag = readn(fd, buf, 1024)) > 0) {
		if(flag == -1)
			ERR_EXIT("READ");
		printf("%d\n", flag);
		writen(STDOUT_FILENO, buf, flag);
	}
	close(fd);
	return 0;
}
