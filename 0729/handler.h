#ifndef _HANDLER_H_
#define _HANDLER_H_
#include "WR.h"
void do_client_select(int fd);
void do_client_poll(int fd);
void do_client_epoll(int fd);
void do_server_select(int fd);
void do_server_poll(int fd);
void do_server_epoll(int fd);
int server_init();
int client_init();
#endif
