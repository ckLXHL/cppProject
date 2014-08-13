#include "Text.h"
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
	while(!ifile.bad() && getline(ifile, len)) {
		handleLine(len);
		readWord(len);
	}
	assert(ifile.eof());
	handleReference();
}

int Text::readWord(const string &st) {
	std::string Word;
	std::istringstream istr(st);
	while(istr >> Word) {
		eachWord_[Word]++;	
	}
	return eachWord_.size();
}

void Text::print() const{
	for(auto &item: eachWord_){
		std::cout << item.first
		<< " " << item.second
		<< std::endl;
	}
	for(auto &item: references_){
		std::cout << "refer " << item.first ;
		for(auto &item1: item.second){
			std::cout << " " << item1.first << " " << item1.second;
		}
		cout << endl;
	}
}

void Text::handleReference() 
{
	for(auto &item: eachWord_){
		references_[item.first[0]][item.first] = item.second;
	}
}

std::string Text::calMatch(const std::string &str) 
{
	timeval ts, te;
	gettimeofday(&ts, NULL);
	std::priority_queue<matchWord> pq;
	for (size_t i = 0; i < 3 && i < str.size(); i++) {
		char firstChar = str[i];
		for(auto &item: references_[firstChar]){
			int matchNum = calLessRound(item.first, str);
			if(matchNum <= (str.size() / 2 + 1))
				pq.push(matchWord(item.first, item.second, matchNum));
		}
	}
	ostringstream os;
	for (int i = 0; !pq.empty(); i++) {
		os << "\t" << pq.top().word_ << endl;
		pq.pop();
	}
	gettimeofday(&te, NULL);
	cout << "查询耗时：" << ts.tv_usec - te.tv_usec << endl;
	return os.str();
}

void Text::writeToFile()const
{
	cout << "write to file" << endl; 
	ofstream os("cache");
	for(auto &item: eachWord_){
		os << item.first << " " 
		   << item.second << endl;
	}
}
