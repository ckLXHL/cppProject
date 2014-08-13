#ifndef SMART_PTR_H
#define SMART_PTR_H 
template <class T> 
class smart_ptr {
	public:
		smart_ptr(const T *ptr): ptr_(ptr), cnt_(new int(1)) { }
		smart_ptr(T *ptr): ptr_(ptr), cnt_(new int(1)) { }
		smart_ptr(): ptr_(0), cnt_(0) { }
		smart_ptr(const smart_ptr& p): ptr_(p.ptr_), cnt_(p.cnt_) { ++*cnt_; }
		~smart_ptr() { if(--*cnt_ == 0) { delete cnt_; delete ptr_; }}
		smart_ptr &operator=(const smart_ptr &); 
		T &operator*() { return *ptr_; }
		T *operator->() { return ptr_; }
	private:
		T *ptr_;
		int *cnt_;
};
template <class T>
inline smart_ptr<T> &smart_ptr<T>::operator=(const smart_ptr<T> &p) {
	if(--*cnt_ == 0) {
		delete cnt_; delete ptr_;
	}
	ptr_ = p.ptr_;
	cnt_ = p.cnt_;
	return *this;
}
#endif  /*SMART_PTR_H*/
