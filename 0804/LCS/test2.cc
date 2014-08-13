#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int dp_buf[2][1024] = {0};
void dp(const string& st1, const string& st2) {
	int *dp1 = dp_buf[0];
	int *dp2 = dp_buf[1];
	for (int i = 0; i < st2.size(); i++) {
		swap(dp1, dp2);
		for (int j = 0; j < st1.size(); j++) {
			if (st2[i] == st1[j]) {
				dp1[j + 1] = dp2[j] + 1;
			} else {
				dp1[j + 1] = max(dp1[j], dp2[j + 1]);
			}
		}
	}
	cout << dp1[st1.size()] << endl;
}
int main() {
	string st1, st2;
	cin >> st1 >> st2;
	dp(st1, st2);
	return 0;
}
