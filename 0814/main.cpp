#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(int argc, const char *argv[])
{
	string st;
	while(cin >> st)
	{
		for (int i = 0; i < st.size(); i++) {
			uint32_t zi = static_cast<unsigned char>(st[i]);
			if (st[i] & 0x80) {
				for(int j = 1; j <= 2; j++)
					zi = (zi << 8) + st[i + j];
				i += 2;
			}
			cout << hex << zi << endl;
			if(zi >= 0xEA84BF && zi <= 0xEAA980)
				st[i] = st[i + 1] = st[i + 2] = ' ';
		}
		cout << st << endl;
	}
	return 0;
}
