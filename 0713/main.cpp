#include "handle.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int main(int argc, const char *argv[])
{
	Handle<int> q(new int(10));
	cout << *q << endl;
	return 0;
}
