#include "cache.h"
#include <algorithm>

void cache::add(std::pair<std::string, std::string> &pr) 
{
	cacher_.push_back(pr);
	if (cacher_.size() > 100)
		cacher_.pop_front();
}
const std::string& isExist(std::string &st)const 
{
	std::find(cacher_.begin(), cacher_.end(), st);
}
