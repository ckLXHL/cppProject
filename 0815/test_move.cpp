#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <cstdlib>
using namespace std;
////const int && add(int a, int b) {
//	int tmp = a + b;
//	return tmp;
//}
struct tmp {
	tmp(tmp &&tm)try: a_(tm.a_) { cout << "move" << endl; }catch(...) {};
	tmp(tmp &tm) :a_(tm.a_) { cout << "refer constr" << endl; }
//	tmp(tmp tm) :a_(tm.a_) { cout << "refer constr" << endl; }
	tmp(int &i)noexcept : a_(i) { cout << "construct" << endl;}
	tmp(int &&i)noexcept : a_(i) { cout << "move construct" << endl; }
	tmp& operator = (tmp &&tm) {
		cout << "no" << endl;
		return *this;
	}
	tmp& operator = (const tmp &tm) {
		cout << "noq" << endl;
		return *this;
	}
	int a_;
};
vector<tmp> add(int a, int b) {
	vector<tmp> vt;
	vt.emplace_back(move(a));
	cout << endl;
	vt.emplace_back(move(b));
	cout << endl;
	vt.emplace_back(10);
	cout << "10 to 15" << endl;
	vt.push_back(15);
	cout << endl;
	vt.emplace_back(20);
	return vt;
}
tmp ne() {
	tmp tt(1);
	cout << "move finish" << endl;
	return tt;
}
int main(int argc, const char *argv[])
{
	vector<tmp> vt2(add(2, 3));
	for(auto &item: vt2){
		cout << item.a_ << endl;	
	}
	cout << (NULL == nullptr) << endl;
	tmp t1(ne());
	cout << t1.a_ << endl;
	return 0;
}
