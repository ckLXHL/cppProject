#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
using namespace std;
template <class T> class my_queue; 
template <class T> ostream& operator << (ostream&, const my_queue<T>&);
template <class T> class my_queueItem {
	friend class my_queue<T>;
	my_queueItem(const T &val): item(val), next(0) { }
	T item;
	my_queueItem *next;
	friend ostream& operator << <T>(ostream&, const my_queue<T>&);
};
template <class T> class my_queue {
	friend ostream& operator << <T>(ostream&, const my_queue<T>&);
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
		ostream& print(ostream&);
		int size;
	private:
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
inline my_queue<T>& my_queue<T>::operator = (const my_queue<T>& Q){
	destroy();
	copy_ele(Q);
}
template <class T>
inline ostream& operator << (ostream& os, const my_queue<T>& q) {
	os << "<";
	my_queueItem<T> * p;
	for(p = q.head; p; p = p->next)
		cout << p->item << " ";
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
inline ostream& my_queue<T>::print(ostream& os){
	my_queueItem<T> * pt = head;
	while(pt != tail){
		os << pt->item << endl;
		pt = pt->next;
	}
	os << pt->item << endl;
	return os;
}
template <class T>
inline void my_queue<T>::destroy(){
	while(!empty())
		pop();
};
