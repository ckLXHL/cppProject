#include "cache.h"
#include <algorithm>
#include <sstream>
void cache::add(const std::string &st1, const std::string &st2) 
{
	cacher_list_.emplace_back(st1, st2);
	cacher_map_[st1] = cacher_list_.end();
	cacher_map_[st1]--;
	if (cacher_list_.size() > 100) {
		cacher_map_.erase(cacher_list_.front().first);
		cacher_list_.pop_front();
	}
}
const std::string cache::isExist(const std::string &st)
{
	map_str_it::iterator it = cacher_map_.find(st);
	if(it != cacher_map_.end()) {
		cacher_list_.push_back(*(it->second));
		cacher_list_.erase(it->second);
		it->second = cacher_list_.end();
		it->second--;
		return cacher_list_.back().second;
	}
	return "";
}
const std::string cache::OutToFile() const {
	std::ostringstream os;
	for(auto &item: cacher_list_){
		os << item.first << " " << item.second << std::endl;
	}
	return os.str();
}
