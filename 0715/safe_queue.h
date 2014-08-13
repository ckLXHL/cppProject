#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
template <class T> class my_queue; 
template <class T> std::ostream& operator << (std::ostream&, const my_queue<T>&);
template <class T> class my_queueItem {
	friend class my_queue<T>;
	friend std::ostream& operator << <T>(std::ostream&, const my_queue<T>&);
	my_queueItem(const T &val): item(val), next(0) { }
	T item;
	my_queueItem *next;
};
template <class T> class my_queue {
	friend std::ostream& operator << <T>(std::ostream&, const my_queue<T>&);
	public:
		my_queue(): size(0),head(0), tail(0) { };
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
		const int getSize()const;
	private:
		int size;
		my_queueItem<T> *head;
		my_queueItem<T> *tail;
		void destroy();
		void copy_ele(const my_queue<T>&);
		template <class it>
		void copy_ele(it, it);
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
inline const int my_queue<T>::getSize() const{
	return size;
}
template <class T>
inline my_queue<T>& my_queue<T>::operator = (const my_queue<T>& Q){
	if (this == &Q) return *this;
	destroy();
	copy_ele(Q);
	return *this;
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
	my_queueItem<T>* pt = head;
	head = head->next;
	size --;
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
	my_queueItem<T> * pt = new my_queueItem<T>(t);
	if(head == 0)
		head = tail = pt;
	else{
		tail->next = pt;
		tail = pt;
	}
	size ++;
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
