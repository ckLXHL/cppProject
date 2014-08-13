#include "buffer.h"

void buffer::push(int num) {
	mu_->lock();
	qu_.push(num);
	mu_->unlock();
}
void pop() {
	mu_->lock();
	while (qu_.empty()) {
		co_->wait(mu_->getlock());
	}
	qu_.pop();
	mu_->unlock();
}
int top()const ｛
｝

bool IsEmpty()const;
