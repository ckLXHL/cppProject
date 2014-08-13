#include "poll_modol.h"
#include "RIO.h"
#include <assert.h>
poll_modol::poll_modol(int listenfd, void (*handle_callback) (int, char*)) :
	listenfd_(listenfd),
	maxi_(0),
	nready_(0),
	handle_callback_(handle_callback) {
		for (int i = 0; i < 2048; i++) {
			clients_[i].fd = -1;
		}
		clients_[0].fd = listenfd_;
		clients_[0].events = POLLIN;
	}
poll_modol::~poll_modol() {};
int poll_modol::IO_do_wait() {
    int nready;
    do{
        nready = poll(clients_, maxi_ + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("poll");
    nready_ = nready;
	IO_handle_accept();
	IO_handle_data();
}
void poll_modol::IO_handle_accept() {
	if (clients_[0].revents & POLLIN) {
		int peerfd = accept(listenfd_, NULL, NULL);
		if(peerfd == -1)
			ERR_EXIT("accept");
		add_fd(peerfd);
	}
}
void poll_modol::IO_handle_data() {
	for(int i = 1; i <= maxi_; ++i)
	{
		int peerfd = clients_[i].fd;
		if(peerfd == -1)
			continue;
		if(clients_[i].revents & POLLIN)
		{
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

			handle_callback_(peerfd, rio.get_buf());

		}
	}
}
void poll_modol::add_fd(int fd)
{
	int i;
    for(i = 1; i < 2048; ++i)
    {
        if(clients_[i].fd == -1)
        {
            clients_[i].fd = fd;
            clients_[i].events = POLLIN;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }
    if(i == 2048)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }
}

void poll_modol::del_fd(int i)
{
    assert(i >= 1 && i < 2048);
    close(clients_[i].fd);
    clients_[i].fd = -1;
}
