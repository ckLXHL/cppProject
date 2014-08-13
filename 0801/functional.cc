#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <functional>
using namespace std;
using namespace std::placeholders;
void add(int a, int b, int c) {
	cout << a << " " << b << " " << c << endl;
}
int main(void)
{
	function<void (int, int)> fp1;
	fp1 = bind(add, _1, _2, 100);
	fp1(1, 2);
	return 0;
}
