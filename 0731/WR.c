#include "WR.h"
ssize_t readn(int fd, void *buf, size_t count) {
	size_t nleft;
	ssize_t nread;		//BUG
	char *ptr;

	ptr = buf;
	nleft = count;

	while (nleft > 0) {
		nread = read(fd, ptr, nleft);
		if (nread < 0) {
			if (errno == EINTR) {
				nread = 0;
			} else {
				return -1;
			}
		} else if (nread == 0) {
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	return count - nleft;
}
ssize_t writen(int fd, const void *buf, size_t count) {
	size_t nleft;
	ssize_t nwritten;   //这里必须是有符号数！！！
	const char *ptr;

	ptr = buf;
	nleft = count;

	while (nleft > 0) {
		nwritten = write(fd, ptr, nleft);
		if (nwritten < 0) {
			if (errno == EINTR) {
				//nwritten = 0;
				continue;
			} else {
				return -1;
			}
		} else if (nwritten == 0) {
			continue;
		}
		nleft -= nwritten;
		ptr += nwritten;
	}

	return count;
}
ssize_t recv_peek(int sockfd, void *buf, size_t len) {
	int nread;
	while (1) {
		nread = recv(sockfd, buf, len, MSG_PEEK);
		if (nread < 0 && errno == EINTR) {	//被中断则继续读取
			continue;
		}
		if (nread < 0) {
			return -1;
		}
		break;
	}
	return nread;
}

ssize_t readline(int sockfd, void *buf, size_t maxline) {
	int nread;	//一次IO读取的数量
	int nleft;	//还剩余的字节数
	char *ptr;	//存放数据的指针的位置
	int ret;	//readn的返回值
	int total = 0;	//目前总共读取的字节数

	nleft = maxline;
	ptr = buf;

	while (nleft > 0) {
		ret = recv_peek(sockfd, ptr, nleft);
		//注意这里读取的字节不够，绝对不是错误！！！
		if (ret <= 0) {
			return ret;
		}

		nread = ret;
		int i;
		for (i = 0; i < nread; ++i) {
			if (ptr[i] == '\n') {
				ret = readn(sockfd, ptr, i + 1);
				if (ret != i + 1) {
					return -1;
				}
				total += ret;
				return total;	//返回此行的长度 '\n'包含在其中
			}
		}

		ret = readn(sockfd, ptr, nread);
		if (ret != nread) {
			return -1;
		}
		nleft -= nread;
		total += nread;
		ptr += nread;
	}
	return maxline;
}
