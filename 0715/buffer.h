#ifndef BUFFER_H_
#define BUFFER_H_ 
#include "safe_queue.h"
#include "th_co.h"
#include "th_mu.h"
class buffer{
	public:
		buffer(int n):
			Que_(), 
			size(n), 
			mutex_(),
			co_con_(),
			co_pro_() { }
		bool IsEmpty();
		int Consum();
		int GetTop()const;
		void Produce(const int&);
		int Get_Size()const;
	private:
		my_queue<int> Que_;
		int size;
		mutable th_mu mutex_;
		th_co co_con_, co_pro_;
};

#endif  /*BUFFER_H_*/
