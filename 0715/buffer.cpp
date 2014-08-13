#include "buffer.h"
bool buffer::IsEmpty(){
	mutex_.lock();
	bool tmp = Que_.empty();
	mutex_.unlock();
	return tmp;
}
int buffer::Consum(){
	mutex_.lock();
	while(Que_.empty()){
		co_con_.wait(mutex_.getlock());
	}
	int ret = Que_.front();
	Que_.pop();
	co_pro_.sig();
	mutex_.unlock();
	return ret;
}
int buffer::GetTop()const{
	mutex_.lock();
	int ret = Que_.front();
	mutex_.unlock();
	return ret;
}
void buffer::Produce(const int& tmp){
	mutex_.lock();
	while(Que_.getSize() >= size){
		co_pro_.wait(mutex_.getlock());
	}
	Que_.push(tmp);
	co_con_.sig();
	mutex_.unlock();
}
int buffer::Get_Size() const{
	mutex_.lock();
	int ret = Que_.getSize();
	mutex_.unlock();
	return ret;
}
