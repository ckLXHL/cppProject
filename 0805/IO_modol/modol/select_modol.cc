#include "select_modol.h"
#include "RIO.h"

select_modol::select_modol(int listenfd, void (*handle_callback) (int, char*)) :
	maxi_(-1),
	maxfd_(listenfd),
	nready_(0),
	listenfd_(listenfd),
	handle_callback_(handle_callback) {
    FD_ZERO(&allset_);
    FD_ZERO(&rset_);
    FD_SET(listenfd_, &allset_);
    for(int i = 0; i < FD_SETSIZE; ++i)
    {
        clients_[i] = -1;
    }
}
select_modol::~select_modol() {
	close(listenfd_);
	for (int i = 0; i < maxi_; i++) {
		(clients_[i] != -1) && (close(clients_[i]));
	}
}
int select_modol::IO_do_wait() {
    rset_ = allset_;
    int nready; 
    do{
        nready = select(maxfd_ + 1, &rset_, NULL, NULL, NULL);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("select");
    nready_ = nready;
	IO_handle_accept();
	IO_handle_data();
	return nready;
}

void select_modol::IO_handle_accept()
{
    if(FD_ISSET(listenfd_, &rset_))
    {
        int peerfd = accept(listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        add_fd(peerfd);
        --nready_;
    }
}

void select_modol::IO_handle_data() 
{
    if(nready_ == 0)
        return ;
    for(int i = 0; i <= maxi_; ++i)
    {
        if((clients_[i] != -1) && FD_ISSET(clients_[i], &rset_))
        {
            int peerfd = clients_[i];
			RIO rio(peerfd);
            int ret = rio.readline(1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("client close\n");
                del_fd(i);
                continue;
            }

            //调用用户自定义的逻辑
            handle_callback_(peerfd, rio.get_buf());
        }
    }
}

void select_modol::add_fd(int fd)
{
    int i;
    for(i = 0; i < FD_SETSIZE; ++i)
    {
        if(clients_[i] == -1)
        {
            clients_[i] = fd;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }


    if(i == FD_SETSIZE)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }

    FD_SET(fd, &allset_);
    if(fd > maxfd_)
        maxfd_ = fd;
}


void select_modol::del_fd(int i)
{
    assert(i >= 0 && i < FD_SETSIZE);
    int fd = clients_[i];
    clients_[i] = -1;
    FD_CLR(fd, &allset_);
    close(fd);
}



