#include "Text.h"
#include "handle.h"
#include <queue>
#include <ctime>
#include <cstdio>
#include <sys/time.h>
#include <string>
using namespace std;

Text::Text(const std::string &str) {
	std::string len;
	std::ifstream ifile(str);
	assert(!ifile.bad());
	while (!ifile.bad() && ifile >> len){
		if (len.size() == 0)
			continue;
		if (len[0] >= '0' && len[0] <= '9')
			continue;
		readWord(len);
	}
	assert(ifile.eof());
	handleReference();
}

void Text::readWord(const string &st) {
		vector<uint32_t> refer = string_handle::translate((Word);
		for(int i = 0; i < refer.size(); i++)
			references_[refer[i]][Word]++;
}

void Text::print() const{
	for(auto &item: references_){
		std::cout << "refer " << item.first ;
		for(auto &item1: item.second){
			std::cout << " " << item1.first << " " << item1.second;
		}
		cout << endl;
	}
}
std::string Text::calMatch(const std::string &str) 
{
	timeval ts, te;
	gettimeofday(&ts, NULL);
	for(auto &item: vec){
			
	}
	std::priority_queue<matchWord> pq;
	for (size_t i = 0; i < 3 && i < str.size(); i++) {
		char firstChar = str[i];
		for(auto &item: references_[firstChar]){
			int matchNum = string_handle::calLessRound(
						   string_handle::translate(item.first),
						   string_handle::translate(str));
			if(matchNum <= (str.size() / 2 + 1))
				pq.push(string_handle::matchWord(item.first, item.second, matchNum));
		}
	}
	ostringstream os;
	for (int i = 0; !pq.empty(); i++) {
		os << "\t" << pq.top().word_ << endl;
		pq.pop();
	}
	cache_.push_back(make_pair(str, os.str()));
	if (cache_.size() > 100)
		cache_.pop_front();
	gettimeofday(&te, NULL);
	cout << "查询耗时：" << ts.tv_usec - te.tv_usec << endl;
	return os.str();
}

void Text::writeToFile()const
{
	cout << "write to file" << endl; 
	ofstream os("cache");
	for(auto &item: cache_){
		os << item.first << " " 
		   << item.second << endl;
	}
}
