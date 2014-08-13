#ifndef ANIMALS_H_
#define ANIMALS_H_ 
#include <iostream>
#include <string>
class dog;
std::ostream &operator<<(std::ostream&, dog&);
std::ostream &operator<<(std::ostream&, cat&);
std::ostream &operator<<(std::ostream&, elephent&);
class animal{
	friend std::ostream &operator<<(std::ostream&, dog&);
	friend std::ostream &operator<<(std::ostream&, cat&);
	friend std::ostream &operator<<(std::ostream&, elephent&);
	public:
		animal(const std::string &name, const std::string &cata):
			name_(name), cata_(cata) { }
		virtual ~animal();
		virtual animal* add() = 0;
	private:
		std::string name_;
		std::string cata_;
};
class dog : public animal {
	friend std::ostream &operator<<(std::ostream&, dog&);
	public:
		dog(const std::string &name, const std::string &cata):
			animal(name, cata) { }
		dog* add();
	private:
		int num_;
};
class cat : public animal {
	friend std::ostream &operator<<(std::ostream&, cat&);
	public:
		cat(const std::string &name, const std::string &cata):
			animal(name, cata) { }
		cat* add();
	private:
		int num_;
};
class elephent : public animal {
	friend std::ostream &operator<<(std::ostream&, elephent&);
	public:
		elephent(const std::string &name, const std::string &cata):
			animal(name, elephenta) { }
		elephent* add();
	private:
		int num_;
};
#endif  /*ANIMALS_H_*/
