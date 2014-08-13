#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/signal.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
// 1.创建socket

// 2.bind

// 3.listen

// 4.accept

//

// close
void do_service(int peerfd)
{
    char recvbuf[1024];
    int ret;
    while(1)
    {
        memset(recvbuf, 0, sizeof recvbuf);
        ret = read(peerfd, recvbuf, 1000);
		printf("read %d\n", ret);
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            return;
        }else if(ret == 0)
			break;
        else
        {
            write(peerfd, recvbuf, strlen(recvbuf));
        }
		sleep(2);
    }
}
void proc(int sig) {
	printf("signal %d\n", sig);
}
int main(int argc, const char *argv[])
{
    //创建socket
	if(signal(SIGPIPE, proc) == SIG_ERR)
		ERR_EXIT("signal");
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");
    //设置端口复用
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8989);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind端口
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof servaddr) < 0)
        ERR_EXIT("bind"); 
    //listen端口
    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");
    int peerfd;
    //accept请求
    if((peerfd = accept(listenfd, NULL, NULL)) < 0)
        ERR_EXIT("accept");
    do_service(peerfd);
    close(peerfd);
    close(listenfd);
    return 0;
}
