#include "TcpServer.h"
#include "Socket.h"
#include "PollPoller.h"
#include <functional>
#include <iostream>
using namespace std;
using namespace std::placeholders;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

TcpServer::TcpServer(const InetAddress &addr)
{
    int sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        ERR_EXIT("socket");
    sock_.reset(new Socket(sockfd));
    sock_->setReusePort();
    sock_->bindAddress(addr);
    sock_->listen();

}


void TcpServer::start()
{
    poller_.reset(new PollPoller(sock_->fd()));
    poller_->setConnectionCallback(onConnect_);
    poller_->setMessageCallback(onMessage_);
    poller_->setCloseCallback(onClose_);

    while(1)
    {
        poller_->poll();
        poller_->handleAccept();
        poller_->handleData();
    }
}


