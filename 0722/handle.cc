#include "handle.h"
handle<T>::handle<T>(handle<T> &a) {
	ptr_ = a->copy();
}
handle<T>::handle(T &a) {
	ptr_ = a.copy();
}
handle &handle::operator=(handle &a) {
	if(this != &a) {
		delete ptr_;
		ptr = a.copy();
	}
}
