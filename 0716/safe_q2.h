#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <memory>
//内存分配类
template <class T> class CachedObj {
	public:
		void *operator new(std::size_t);
		void operator delete(void *, std::size_t);
		virtual ~CachedObj() { }
	protected:
		T *next;
	private:
		static void add_to_freelist(T*);
		static std::allocator<T> alloc_mem;
		static T *freeStore;
		static const std::size_t chunk;
};
template <class T>
void *CachedObj<T>::operator new(size_t sz){
	if (sz != sizeof(T))
		throw std::runtime_error("CachedObj: wrong size object in operator new");
	if (!freeStore) {
		T *array = alloc_mem.allocate(chunk);
		for (size_t i = 0; i != chunk; ++i)
			add_to_freelist(&array[i]);
	}
	T *p = freeStore;
	freeStore = freeStore->CachedObj<T>::next;
	return p;
}
template <class T>
void CachedObj<T>::operator delete(void *p, size_t){
	if (p != 0)
		add_to_freelist(static_cast<T*>(p));
}
template <class T>
void CachedObj<T>::add_to_freelist(T *p){
	p->CachedObj<T>::next = freeStore;
	freeStore = p;
}
template <class T> std::allocator<T> CachedObj<T>::alloc_mem;
template <class T> T *CachedObj<T>::freeStore = 0;
template <class T> const size_t CachedObj<T>::chunk = 24;
template <class T> class my_queue; 
template <class T> std::ostream& operator << (std::ostream&, const my_queue<T>&);
//私有结点类
/*
template <class T>
class my_queueItem: public CachedObj< my_queueItem<T> > {
	friend class my_queue<T>;
	friend std::ostream& operator << <T>(std::ostream&, const my_queue<T>&);
	my_queueItem(const T &val): item(val), next(0) { }
	T item;
	my_queueItem *next;
};
*/
//队列模板类
template <class T> class my_queue {
	struct my_queueItem;
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
		struct my_queueItem: public CachedObj< my_queueItem > {
			my_queueItem(const T &val): item(val), next(0) { }
			T item;
			my_queueItem *next;
		};
		int size;
		my_queueItem *head;
		my_queueItem *tail;
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
	destroy();
	copy_ele(Q);
}
template <class T>
inline std::ostream& operator << (std::ostream& os, const my_queue<T>& q) {
	os << "<";
	my_queue<T>::my_queueItem *p;
	for(p = q.head; p; p = p->next)
		std::cout << p->item << " ";
	os << ">";
	return os;
}
template <class T> 
inline void my_queue<T>::pop(){
	my_queueItem* pt = head;
	head = head->next;
	size --;
	delete pt;
}
template <class T> 
inline void my_queue<T>::copy_ele(const my_queue& q){
	my_queueItem* pt = q.head;
	while(pt != q.tail){
		push(pt->item);
		pt = pt->next;
	}
	push(pt->item);
}
template <class T> 
inline void my_queue<T>::push(const T& t){
	my_queueItem * pt = new my_queueItem(t);
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
	my_queueItem * pt = head;
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
