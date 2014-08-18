#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctype.h>
#include <list>
using namespace std;
int main(int argc, const char *argv[])
{
	list<int> ls;
	locale def;
	cout << def.name() << endl;
	locale current = cout.getloc();
	cout << current.name() << endl;
	float val = 1234.56;
	cout << val << endl;
	cout.imbue(locale("chs"));
	wstring sst;
	wcin >> sst;
	current = cout.getloc();
	cout << current.name() << endl;
	cout << val << endl;
	wstring ws;
	wcout.imbue(std::locale("C"));
	while(wcin >> ws) {
		wcout << ws << endl;
	}
	return 0;
}
