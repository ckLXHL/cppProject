#ifndef __THREAD_H__
#define __THREAD_H__
#include <pthread.h>
#include <stdexcept>
#include "safe_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
class th_mu;
class th_co;
class thread{
	public:
		thread(int a, my_queue<int> *b): it(-1), cha(a), p(b){ }
		~thread() { }
		static void* thread_func(void* arg){ 
			thread *p = static_cast<thread*>(arg);
			p->run();
		}
		void start(){
			pthread_create(&it, NULL, thread_func, this);
		}
		void run();
		void join() {
			pthread_join(it,NULL);
		}
	private:
		pthread_t it;
		my_queue<int> * p;
		int cha;
};
#endif  /*thread*/
