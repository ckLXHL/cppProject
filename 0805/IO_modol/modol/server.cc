#include "RIO.h"
#include "epoll_modol.h"
#include "poll_modol.h"
#include "select_modol.h"
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory>
int get_listen_fd();
void handler(int fd, char *buf)
{
	RIO rio(fd);
    printf("recv data : %s", buf);
	rio.copy_buf(buf);
	rio.writen(strlen(buf));
}


int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
    int listenfd = get_listen_fd();
	//std::shared_ptr<IO_modol> ep(new select_modol(listenfd, handler));
	//std::shared_ptr<IO_modol> ep(new poll_modol(listenfd, handler));
	std::shared_ptr<IO_modol> ep(new epoll_modol(listenfd, handler));
    while(1)
    {
		ep->IO_do_wait();
    }
    return 0;
}

int get_listen_fd()
{
    //创建socket
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

    return listenfd;
}

