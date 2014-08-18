#include "cacheManager.h"
#include <fstream>
#include <assert.h>
cache& cacheManager::goCache()
{
	MutexLockGuard guard(mutex_);
	while(isFull()) 
		full_.wait();
	return findCache();
}
cache& cacheManager::findCache()
{
	size_t i;
	for (i = 0; i < cachers_.size(); i++) {
		if (!cachers_[i].isHold()) {
			cachers_[i].Hold();
			Full_++;
			break;
		}
	}
	assert(i < cachers_.size());
	return cachers_[i];
}
void cacheManager::writeToFile() const {
	std::fstream os("./log/cache");
	for(auto &item: cachers_){
		os << item.OutToFile();
	}
	os.close();
}
