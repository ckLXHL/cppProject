#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <stdexcept>
#include <stdio.h>
#include <fstream>
#include <sstream>
using namespace std;
struct stu {
	int num_ ;
	string name_;
	double score;
	void print(ostream &os){
		os << num_ << name_ << score << endl;

	}
};
int main(int argc, const char *argv[])
{
	string s;
	ifstream in("test.cpp");
	ofstream ou("ouou", ofstream::app);
	while(getline(in,s))
		ou << s << endl;
	in.close();
	ou.close();
	stu caokai;
	ostringstream ostr;
	caokai.name_ = "caokai";
	caokai.num_ = 10;
	caokai.score = 99.9;
	caokai.print(cout);
	caokai.print(ostr);
	cout << ostr.str() << endl;
	return 0;
}
