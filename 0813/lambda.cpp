#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;
int main(int argc, const char *argv[])
{
	int i = 10;
	function<int ()> ft = [i] ()mutable { return ++i; };	
	cout << ft() << endl;
	return 0;
}
