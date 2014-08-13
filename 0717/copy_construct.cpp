#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
class person {
	public:
		person(const string& a, int b, double c): 
			name_(a),
			age_(b),
			score_(c) { }
		person(const person& oth):
			name_("kkkkkkk"),
			age_(oth.age_),
			score_(oth.score_) { }
		void print() {
			cout << "name is " << name_
				<< "age is " << age_
				<< "score is" << score_ << endl;
		}
	private:
		string name_;
		int age_;
		double score_;
};
int main() {
	person p1("caokai", 4, 10.5);
	p1.print();
	person p2(p1);
	p2.print();
	person p3 = p2;
	p3.print();
	return 0;
}
