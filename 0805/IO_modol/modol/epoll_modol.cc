#include "epoll_modol.h"
#include "RIO.h"
epoll_modol::epoll_modol(int listenfd, void (*handle_callback) (int, char*)) :
	listenfd_(listenfd),
	nready_(0),
	handle_callback_(handle_callback) {
		if((epollfd_ = epoll_create(2048)) == -1)
			ERR_EXIT("epoll_create");
		add_fd(listenfd_);
	}

epoll_modol::~epoll_modol() {
	close(epollfd_);
	close(listenfd_);
};
int epoll_modol::IO_do_wait() {
    int nready;
    do{
        nready = epoll_wait(epollfd_,
                            events_,
                            2048,
                            -1);
    }while(nready == -1 && errno == EINTR);

    if(nready == -1)
        ERR_EXIT("epoll_wait");
    nready_ = nready;
	handle();
}
void epoll_modol::IO_handle_accept() {
    int peerfd = accept(listenfd_, NULL, NULL);
    if(peerfd == -1)
        ERR_EXIT("accept");
    add_fd(peerfd);
}
void epoll_modol::IO_handle_data(int peerfd) {
	RIO rio(peerfd);
    int ret = rio.readline(1024);
    if(ret == -1)
        ERR_EXIT("readline");
    else if(ret == 0)
    {
        printf("client close\n");
        del_fd(peerfd);
        return ;
    }

    handle_callback_(peerfd, rio.get_buf());
}
void epoll_modol::add_fd(int fd) {
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
    if(epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}
void epoll_modol::del_fd(int fd) {
    struct epoll_event ev;
    ev.data.fd = fd;
    if(epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &ev) == -1)
        ERR_EXIT("epoll_ctl");
}
void epoll_modol::handle() {
    int i;
    for(i = 0; i < nready_; ++i)
    {
        int fd = events_[i].data.fd;
        if(fd == listenfd_)
            IO_handle_accept();
        else
            IO_handle_data(fd);
    }
}
