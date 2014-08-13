#ifndef __THREAD_H__
#define __THREAD_H__
#include <pthread.h>
#include <unistd.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include "buffer.h"
class thread{
	public:
		thread(buffer& b): buf_(b){ }
		~thread() { }
		static void* thread_func(void* arg){ 
			thread *p = static_cast<thread*>(arg);
			p->run();
			return NULL;
		}
		void start(){
			pthread_create(&it_, NULL, thread_func, this);
		}
		virtual void run() {};
		void join() {
			pthread_join(it_,NULL);
		}
	protected:
		buffer& buf_;
	private:
		pthread_t it_;
};
class Produc_Thread: public thread{
	public:
		Produc_Thread(buffer& c): thread(c){ }
		void run();
};
class Consum_Thread: public thread{
	public:
		Consum_Thread(buffer& c): thread(c){ }
		void run();
};
#endif  /*thread*/
