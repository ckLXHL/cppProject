#ifndef BUFFER_H
#define BUFFER_H 

#include <queue>
#include <memory>
//前向声明
class th_co;
class th_mu;
class buffer {
	public:
		buffer(std::share_ptr<th_co> s1, 
			   std::share_ptr<th_mu> s2): 
			qu_(), co_(s1), mu_(s2) {}
		void push(int);
		void pop();
		int top()const;
		bool IsEmpty()const;
	private:
		std::queue<int> qu_;
		std::share_ptr<th_co> co_;
		mutable std::share_ptr<th_mu> mu_;
};

#endif  /*BUFFER_H*/
