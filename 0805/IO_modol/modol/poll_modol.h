#ifndef POLL_MODOL_H
#define POLL_MODOL_H 
#include "IO_modol.h"
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class poll_modol : public IO_modol {
	public:
		poll_modol(int listenfd, void (*handle_callback) (int, char*));
		~poll_modol();
		virtual int IO_do_wait();
		virtual void IO_handle_accept();
		virtual void IO_handle_data();
	private:
		void add_fd(int);
		void del_fd(int);
		struct pollfd clients_[2048];
		int listenfd_;
		int maxi_;   //最大数组下标
		int nready_;   
		void (*handle_callback_) (int, char *); //回调函数
};
#endif  /*POLL_MODOL_H*/
