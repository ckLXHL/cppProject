#ifndef EPOLL_MODOL_H
#define EPOLL_MODOL_H 
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include "IO_modol.h"
class epoll_modol : public IO_modol {
	public:
		epoll_modol(int listenfd, void (*handle_callback) (int, char*));
		~epoll_modol() ;
		virtual int IO_do_wait();
		virtual void IO_handle_accept();
		virtual void IO_handle_data(int);
	private:
		void handle();
		void add_fd(int fd);
		void del_fd(int fd);
		int epollfd_;
		int listenfd_;
		struct epoll_event events_[2048];
		int nready_;
		void (*handle_callback_) (int, char *);
};
#endif  /*EPOLL_MODOL_H*/
