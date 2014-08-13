#include "safe_q2.h"
#include <string>
#include <typeinfo>
using namespace std;
int main() {
	my_queue<string> q;
	string b;
	char base[10];
	char* kk;
	int aa[10];
	int a* = aa[9];
	cout << typeid(base).name() << endl;
	cout << typeid(kk).name() << endl;
	cout << typeid(aa).name() << endl;
	return 0;
}
