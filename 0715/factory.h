#ifndef FACTORY_H
#define FACTORY_H 
#include "buffer.h"
#include "thread.h"
#include <vector>
class factory {
	public:
		factory(int a, int b, int c):
			buf_size_(a), 
			buf_(a),
			produc_size_(b),
			consum_size_(c),
			Pros_(produc_size_, Produc_Thread(buf_)),
			Cons_(consum_size_, Consum_Thread(buf_)){ }
		void run_thread_();
	private:
			int buf_size_;
			buffer buf_;
			int produc_size_;
			int consum_size_;
			std::vector<Produc_Thread> Pros_;
			std::vector<Consum_Thread> Cons_;
};
#endif  /*FACTORY_H*/
