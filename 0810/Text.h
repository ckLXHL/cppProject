#ifndef TEXT_H
#define TEXT_H 
#include <string>
#include <unordered_map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <stdexcept>
#include <list>
#define ERR_EXIT(m) \
	do { \
		perror(m);\
		exit(EXIT_FAILURE);\
	}while(0)
class Text {
	public:
		Text (const std::string &);
		~Text () {};
		void print()const;
		std::string calMatch(const std::string&);
		bool Match(const std::string &st) 
		{ return library_.find(st) != library_.end(); }
	private:
		//处理初始化
		void readWord(const std::string&);//读入所有词汇
		std::unordered_map<std::string, int> library_;
		std::unordered_map<uint32_t, std::unordered_map<std::string, std::vector<uint32_t> > > references_;
};
#endif  /*TEXT_H*/
