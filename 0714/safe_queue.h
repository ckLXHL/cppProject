#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
class th_mu{
	public:
		th_mu(){
			if(pthread_mutex_init(&mt, NULL))
				throw std::runtime_error("mutex init fail");
		}
		~th_mu(){
			if(pthread_mutex_destroy(&mt))
				throw std::runtime_error("mutex des fail");
		}
		void lock(){
			pthread_mutex_lock(&mt);
		}
		pthread_mutex_t& getlock(){
			return mt;
		}
		void unlock(){
			pthread_mutex_unlock(&mt);
		}
	private:
		pthread_mutex_t mt;
};
class th_co{
	public:
		th_co(){
			if(pthread_cond_init(&ct, NULL))
				throw std::runtime_error("cond init fail");
		}
		virtual ~th_co(){
			if(pthread_cond_destroy(&ct))
				throw std::runtime_error("cond des fail");
		}
		void wait(pthread_mutex_t& mu){
			if(pthread_cond_wait(&ct, &mu))
				throw std::runtime_error("con wait fail");
		}
		void sig(){
			pthread_cond_signal(&ct);
		}
	private:
		pthread_cond_t ct;
};
template <class T> class my_queue; 
template <class T> std::ostream& operator << (std::ostream&, const my_queue<T>&);
template <class T> class my_queueItem {
	friend class my_queue<T>;
	my_queueItem(const T &val): item(val), next(0) { }
	T item;
	my_queueItem *next;
	friend std::ostream& operator << <T>(std::ostream&, const my_queue<T>&);
};
template <class T> class my_queue {
	friend std::ostream& operator << <T>(std::ostream&, const my_queue<T>&);
	public:
		my_queue(): head(0), tail(0), size(0) { };
		my_queue(const my_queue<T>& q): head(0), tail(0), size(0) { copy_ele(q); };
		template <class it> 
			my_queue(it beg, it end):
				head(0), tail(0) { copy_ele(beg, end); }
		~my_queue() { destroy(); }
		my_queue& operator = (const my_queue&);
		template <class it>
			void assign(it, it);
		void push(const T&);
		void pop();
		bool empty(){ return head == 0; }
		T& front(){ return head->item; }
		const T& front() const { return head->item; };
		std::ostream& print(std::ostream&);
	private:
		int size;
		my_queueItem<T> *head;
		my_queueItem<T> *tail;
		void destroy();
		void copy_ele(const my_queue<T>&);
		template <class it>
		void copy_ele(it, it);
		th_mu mu1;
		th_co co1, co2;
};
template <class T> template <class it>
inline void my_queue<T>::assign(it beg, it end){
	destroy();
	copy_ele(beg, end);
}
template <class T> template <class it>
inline void my_queue<T>::copy_ele(it beg, it end){
	while(beg != end){
		push(*beg);
		beg++;
	}
}
template <class T>
inline my_queue<T>& my_queue<T>::operator = (const my_queue<T>& Q){
	destroy();
	copy_ele(Q);
}
template <class T>
inline std::ostream& operator << (std::ostream& os, const my_queue<T>& q) {
	os << "<";
	my_queueItem<T> * p;
	for(p = q.head; p; p = p->next)
		std::cout << p->item << " ";
	os << ">";
	return os;
}
template <class T> 
inline void my_queue<T>::pop(){
	mu1.lock();
	while(empty())
		co1.wait(mu1.getlock());
	my_queueItem<T>* pt = head;
	head = head->next;
	size --;
	std::cout << "pop some thing" << std::endl;
	co2.sig();
	mu1.unlock();
	delete pt;
}
template <class T> 
inline void my_queue<T>::copy_ele(const my_queue& q){
	my_queueItem<T>* pt = q.head;
	while(pt != q.tail){
		push(pt->item);
		pt = pt->next;
	}
	push(pt->item);
}
template <class T> 
inline void my_queue<T>::push(const T& t){
	mu1.lock();
	while(size >= 10)
		co2.wait(mu1.getlock());
	my_queueItem<T> * pt = new my_queueItem<T>(t);
	if(head == 0)
		head = tail = pt;
	else{
		tail->next = pt;
		tail = pt;
	}
	std::cout << front() << " push this" << std::endl;
	size ++;
	co1.sig();
	mu1.unlock();
}
template <class T>
inline std::ostream& my_queue<T>::print(std::ostream& os){
	my_queueItem<T> * pt = head;
	while(pt != tail){
		os << pt->item << std::endl;
		pt = pt->next;
	}
	os << pt->item << std::endl;
	return os;
}
template <class T>
inline void my_queue<T>::destroy(){
	while(!empty())
		pop();
};
#endif
