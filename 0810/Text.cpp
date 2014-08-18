#include "Text.h"
#include "handle.h"
#include <queue>
#include <ctime>
#include <cstdio>
#include <sys/time.h>
#include <fstream>
#include <string>
using namespace std;
Text::Text(const std::string &str) {
	std::string len;
	std::ifstream ifile(str);
	assert(!ifile.bad());
	while (!ifile.bad() && ifile >> len){
		if (len.size() == 0)
			continue;
		readWord(len);
	}
	assert(ifile.eof());
	ifile.close();
}

void Text::readWord(const string &st) {
	if (library_[st]++ == 0) {
		vector<uint32_t> refer = string_handle::translate(st);
		references_[refer[0]][st] = refer;
	}
}

void Text::print() const{
	for(auto &item: library_){
		cout << item.first << " " << item.second << endl;	
	}
	for(auto &item: references_){
		std::cout << "refer " << item.first ;
		for(auto &item1: item.second){
			std::cout << item1.first << " ";
		}
		cout << endl;
	}
}
std::string Text::calMatch(const std::string &str) 
{
	timeval ts, te;
	gettimeofday(&ts, NULL);
	std::vector<uint32_t> refer = string_handle::translate(str);
	std::priority_queue<string_handle::matchWord> pq;
	for (size_t i = 0; i < 3 && i < str.size(); i++) {
		uint32_t firstChar = refer[0];
		for(auto &item: references_[firstChar]){
			int matchNum = string_handle::calLessRound(item.second, refer);
			if(matchNum <= (str.size() / 2))
				pq.push(string_handle::matchWord(item.first, library_[item.first], matchNum));
		}
	}
	ostringstream os;
	for (int i = 0; !pq.empty() && i < 10; i++) {
		os << "\t" << pq.top().word_ << endl;
		pq.pop();
	}
	gettimeofday(&te, NULL);
	cout << "查询耗时：" << te.tv_usec - ts.tv_usec << endl;
	return os.str();
}
