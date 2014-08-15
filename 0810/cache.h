#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "NonCopyable.h"
class cache : NonCopyable
{
	public:
		cache(): hold(false), cacher() {};
		bool isHold()const{ return hold; }
		void add(std::pair<std::string, std::string>&);
		const std::string& isExist(std::string&)const;
	private:
		bool hold;
		std::list<std::pair<std::string, std::string> > cacher_;
};
