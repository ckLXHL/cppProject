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
	function<int (initializer_list<string>)> func = 
		[] (initializer_list<string>ls) ->int {
			for(auto &item: ls){
				cout << item << endl;
			}
			cout << "size is " << ls.size() << endl;
			return ls.size();
		}; 
	int size = func({"caokai", "guoxiong", "dsfds", "haiyou shenme"});
	cout << size << endl;
	return 0;
}
