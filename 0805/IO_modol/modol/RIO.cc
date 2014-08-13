#include "RIO.h"
RIO::RIO(const int fd):fd_(fd) {
	memset(buf_, 0, sizeof buf_);
}
ssize_t RIO::readn(int len) {
    size_t nleft = len; //表示还需要读取的字节数
    ssize_t nread;
    char *bufp = buf_; //控制read函数存放的位置

    while(nleft > 0)
    {
        if((nread = read(fd_, bufp, nleft)) == -1)
        {
            if(errno == EINTR)  //interupt
                nread = 0;  //continue;  中断需要再次读取
            else
                return -1;  // ERROR
        }else if(nread == 0)  // EOF
            break;
        
        nleft -= nread;
        bufp += nread;
    }
    return (len - nleft);
}
ssize_t RIO::recv_peek(int len) {
    int nread;
    while (1) {
        //这个过程只成功调用一次
        nread = recv(fd_, buf_, len, MSG_PEEK);
        if (nread < 0 && errno == EINTR) {  //被中断则继续读取
            continue;
        }
        if (nread < 0) {
            return -1;
        }
        break;
    }
    return nread;
}
void RIO::copy_buf(char *buf) {
	strcpy(buf_, buf);
}

ssize_t RIO::writen(int len) {
    size_t nleft = len;
    ssize_t nwrite;

    char *bufp = buf_;

    while(nleft > 0)
    {
        //nwrite == 0也属于错误
        if((nwrite = write(fd_, bufp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1; // -1 和 0
        }

        nleft -= nwrite;
        bufp += nwrite;
    }
    return len;  //这里不是 n- nleft 必须是n
}
ssize_t RIO::readline(int maxlen) {
    int nread;  //一次IO读取的数量
    int nleft;  //还剩余的字节数
    char *ptr;  //存放数据的指针的位置
    int ret;    //readn的返回值
    int total = 0;  //目前总共读取的字节数

    nleft = maxlen - 1;
    ptr = buf_;

    while (nleft > 0) {
        //这一次调用仅仅是预览数据
        //并没有真的把数据从缓冲区中取走
        ret = recv_peek(nleft);
        //注意这里读取的字节不够，绝对不是错误！！！
        if (ret <= 0) {
            return ret;
        }

        nread = ret;
        int i;
        for (i = 0; i < nread; ++i) {
            if (ptr[i] == '\n') {
                //这里才是真正的读取过程
                ret = readn(i + 1);
                if (ret != i + 1) {
                    return -1;
                }
                total += ret;
                ptr += ret;
                *ptr = 0;
                return total;   //返回此行的长度 '\n'包含在其中
            }
        }
        //如果没有发现\n，这些数据应全部接收
        ret = readn(nread);
        if (ret != nread) {
            return -1;
        }
        nleft -= nread;
        total += nread;
        ptr += nread;
    }
    *ptr = 0;
    return maxlen - 1;
}
char *RIO::get_buf() {
	return buf_;
}
