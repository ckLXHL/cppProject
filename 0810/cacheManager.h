#ifndef CACHEMANAGER_H
#define CACHEMANAGER_H 

#include "cache.h"
#include "Condition.h"
#include "MutexLock.h"
#include <vector>
class cacheManager : NonCopyable
{
	public:
		cacheManager(size_t i):Full_(0), full_(mutex_), cachers_(i, cache()){};
		bool isFull() { return Full_ == cachers_.size(); }
		cache& goCache();
		void writeToFile() const;
	private:
		cache& findCache();
		size_t Full_;
		MutexLock mutex_;
		Condition full_;
		std::vector<cache> cachers_;
};
#endif  /*CACHEMANAGER_H*/
