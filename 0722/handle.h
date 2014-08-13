#ifndef HANDLE_H
#define HANDLE_H 
template<class T>
class handle{
	public:
		handle(): ptr_(0) { };
		handle(handle&);
		handle(T&);
		handle &operator=(handle&);
		virtual ~handle() { delete ptr_; };
	private:
		T *ptr_;
};
#endif  /*HANDLE_H*/
