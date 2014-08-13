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
		{ return eachWord_.find(st) != eachWord_.end(); }
		void writeToFile()const;
	private:
		int calLessRound(const std::string& ,const std::string&);
		//处理初始化
		int readWord(const std::string&);//读入所有词汇
		void handleLine(std::string &)const;//去符号，转换为小写字母
		void handleReference();//对所有词汇编写索引
		std::unordered_map<std::string, int> eachWord_;
		std::unordered_map<char, std::unordered_map<std::string, int> > references_;
	//内嵌匹配类
};
#endif  /*TEXT_H*/