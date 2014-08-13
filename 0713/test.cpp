#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
using namespace std;
template <class T> class Handle {
	public:
		Handle(T *p = 0): ptr(p), use(new size_t(1)) { }
		T& operator*();
		T* operator->();
		const T& operator*() const;
		const T* operator->() const;
		Handle(const Handle& h): ptr(h.ptr), use(h.use) { ++*use; }
		Handle& operator = (const Handle&);
		~Handle() { rem_ref(); }
	private:
		T* ptr;
		size_t* use;
		void rem_ref() { if( --*use == 0) { delete ptr; delete use; } }
};
template <class T>
Handle<T>& Handle<T>::operator = (const Handle<T>& H) {
	rem_ref();
	ptr = H.ptr;
	use = H.ptr;
	++*use;
	return *this;
}
template <class T>
T& Handle<T>::operator*(){
	if(ptr) return *ptr;
	throw std::runtime_error("dereference of unbind Handle");
}
template <class T>
const T& Handle<T>::operator*() const {
	if(ptr) return *ptr;
	throw std::runtime_error("dereference of unbind Handle");
}
template <class T>
T* Handle<T>::operator->() {
	if(ptr) return ptr;
	throw std::runtime_error("access through unbound Handle");
}
template <class T>
const T* Handle<T>::operator->() const {
	if(ptr) return ptr;
	throw std::runtime_error("access through unbound Handle");
}
int main(int argc, const char *argv[])
{
	Handle<int> q(new int(10));
	cout << *q << endl;
	return 0;
}
