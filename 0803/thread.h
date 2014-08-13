#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <functional>
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
class thread {
	public:
		thread(const std::function<int ()> &fun):pid_(), run_(fun) { };
		//constructor
		static void* pass(void *arg) { 
			thread* thr = static_cast<thread*>(arg);
			int ret = thr->run_();
			pthread_exit((void*)ret);
		};
		void create() {
			if(pthread_create(&pid_, NULL, pass, this))
				ERR_EXIT("pthread_create");
		}
		void join() const {
			int ret;
			if(pthread_join(pid_, (void**)&ret))
				ERR_EXIT("pthread_join");
			printf("thread return %s\n", 
				!ret ? "success" : "failure");
		}
	private:
		pthread_t pid_;
		std::function<int ()> run_;
};
class thread_pool {
	public:
		thread_pool(int num, const std::function<int ()>& fun) : 
			thread_num_(num), 
			run_(fun),
			vt(thread_num_, thread(run_)) {};
		void pool_start() {
			for (auto &item: vt)
				item.create();
			for (auto &item: vt)
				item.join();
		}
	private:
		int thread_num_;
		std::function<int ()> run_;
		std::vector<thread> vt;
};
