#ifndef COMPLEX_H
#define COMPLEX_H 
#include <iostream>
#include <cmath>
class complex_num {
	friend std::ostream &operator<<(std::ostream&, complex_num&);
	friend std::ostream &operator<<(std::ostream&, const complex_num&);
	friend std::istream &operator>>(std::istream&, complex_num&);
	friend complex_num operator+(const complex_num&, const complex_num&);
	friend complex_num operator-(const complex_num&, const complex_num&);
	friend complex_num operator*(const complex_num&, const complex_num&);
	public:
		complex_num(int r, int im): real_(r), image_(im) { }
		complex_num(): real_(0), image_(0) { }
		~complex_num() { }
		complex_num &operator=(const complex_num &cm) { real_ = cm.real_; image_ = cm.image_; return *this;}
		const double real_value() const ;
	private:
		int real_;
		int image_;
};
#endif  /*COMPLEX_H*/

