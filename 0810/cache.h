#ifndef CACHE_H
#define CACHE_H 

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>
class cache
{
	public:
		typedef std::list<std::pair<std::string, std::string> > list_pair;
		typedef std::unordered_map<std::string, list_pair::iterator> map_str_it;
		cache(): hold_(false) {};
		bool isHold()const{ return hold_; }
		void add(const std::string&, const std::string&);
		const std::string isExist(const std::string&);
		void Hold() { hold_ = true; }
		void deHold() { hold_ = false; }
		const std::string OutToFile() const;
	private:
		bool hold_;
		list_pair cacher_list_;
		map_str_it cacher_map_;
};
#endif
