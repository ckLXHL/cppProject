#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
class LongestComString{ 
	public:
		LongestComString(const string &st1, const string &st2):
			str1_(st1), str2_(st2), 
			v1_(str1_.size() + 1, 0), v2_(str1_.size() + 1, 0) {};
		void dp();
	private:
		const string &str1_;
		const string &str2_;
		vector<int> v1_;
		vector<int> v2_;
};
void LongestComString::dp() {
	for(size_t i = 1; i <= str2_.size(); i++) {
		swap(v1_, v2_);
		for(size_t j = 1; j <= str1_.size(); j++) {
			if(str2_[i - 1] == str1_[j - 1])	
				v2_[j] = v1_[j - 1] + 1;
			else
				v2_[j] = max(v2_[j - 1], v1_[j]);
		}
	}
	cout << v2_[str1_.size()] << endl;
}
int main(int argc, char *argv[])
{
	string st1;
	string st2;
	cin >> st1 >> st2;
	LongestComString dp(st1, st2);
	dp.dp();
	return 0;
}
