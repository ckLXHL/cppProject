#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, const char *argv[])
{
	string st;
	while (cin >> st) {
		for (int i = 0; i < st.size(); i += 3) {
			cout << "首位为：" << ((unsigned)st[i] & 0x000000ff) << endl;
			cout << st.substr(i, 3) << endl;
			if ((st[i] & 0xff) == 0xA1 && (st[i + 1] & 0xff) ==0xA3)
				cout << "ispunct" << endl;
		}
	}
	return 0;
}
