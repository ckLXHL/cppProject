#include "complex.h"
#include <iostream>
using namespace std;
ostream &operator<<(ostream &os, complex_num &cm) {
	os << "real num is " << cm.real_ 
		<< " image num is " << cm.image_;
	return os;
}
ostream &operator<<(ostream &os, const complex_num &cm) {
	os << "real num is " << cm.real_ 
		<< " image num is " << cm.image_;
	return os;
}
istream &operator>>(istream &is, complex_num &cm) {
	is >> cm.real_ >> cm.image_;
	return is;
}
complex_num operator+(const complex_num &cm1, const complex_num &cm2) {
	return complex_num(cm1.real_ + cm2.real_, cm1.image_ + cm2.image_);
}
complex_num operator-(const complex_num &cm1, const complex_num &cm2) {
	return complex_num(cm1.real_ - cm2.real_, cm1.image_ - cm2.image_);
}
complex_num operator*(const complex_num &cm1, const complex_num &cm2) {
	int real = cm1.real_ * cm2.real_ - cm1.image_ * cm2.image_;
	int image = cm1.real_ *cm2.image_ + cm1.image_ * cm2.real_;
	return complex_num(real, image);
}
const double complex_num::real_value() const {
	double ret = static_cast<double>(real_ * real_ + image_ * image_);
	ret = sqrt(ret);
	return ret;
}
