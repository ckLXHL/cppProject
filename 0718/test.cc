#include "complex.h"
#include "smart_ptr.h"
#include <iostream>
using namespace std;
int main(int argc, const char *argv[])
{
	smart_ptr<complex_num> t1(new complex_num(100,2));
	complex_num cm6 = *t1;
	cout << *t1 << endl;
	cout << cm6 << endl;
	complex_num cm1(1, 2);
	cout << cm1 << endl;
	complex_num cm2(cm1);
	cout << cm2 << endl;
	complex_num cm3 = cm1 + cm2;
	cout << cm3 << endl;
	complex_num cm4 = cm1 * cm2;
	cout << cm4 << endl;
	cout << cm4.real_value() << endl;
	const complex_num cm5 = cm1 * cm2;
	cout << cm5 << endl;
	return 0;
}
