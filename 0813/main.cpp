#include <string>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
using namespace std;
bool Ishanzi(string &st)
{
	for (int i = 0; i < st.size(); i++)
	{
		if ((st[i] & 0x80)) {
			cout << "一个汉字：" << st.substr(i, 3) << endl;
			i += 2;
		} else
			cout << "一个字符：" << st[i] << endl;
	}
}
int main(int argc, const char *argv[])
{
	string str;
	while(cin >> str)
		Ishanzi(str);
	return 0;
}
