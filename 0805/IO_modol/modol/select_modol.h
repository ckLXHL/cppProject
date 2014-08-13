#ifndef SELECT_MODOL_H
#define SELECT_MODOL_H 
#include "IO_modol.h"
#include <sys/select.h>
#include <sys/types.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)

class select_modol : public IO_modol {
	public:
		select_modol(int listenfd, void (*handle_callback) (int, char*));
		~select_modol();
		virtual int IO_do_wait();
		virtual void IO_handle_accept();
		virtual void IO_handle_data();
	private:
		void add_fd(int);
		void del_fd(int);
		fd_set allset_;
		fd_set rset_;
		int clients_[FD_SETSIZE];
		int maxi_;
		int maxfd_;
		int nready_;
		int listenfd_;
		void (*handle_callback_) (int , char *);
};
#endif  /*SELECT_MODOL_H*/
