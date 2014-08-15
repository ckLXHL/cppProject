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
		{   uint32_t fir = string_handle::Zi(st);
			return references_[fir].find(st) != references_[fir].end(); }
		void writeToFile()const;
	private:
		//处理初始化
		int readWord(const std::string&);//读入所有词汇
		void handleReference(const std::string&);//对所有词汇编写索引
		std::unordered_map<uint32_t, std::unordered_map<std::string, int> > references_;
		std::list<std::pair<string, string> > cache_;
	//内嵌匹配类
};
#endif  /*TEXT_H*/
