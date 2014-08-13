#include "animals.h"
std::ostream &operator<<(std::ostream&, dog &a) {
	cout << "dog name is " << dog.name_ 
		<< "dog cata is " << dog.cata_
		<< "dog num is " << dog.num_;
}
std::ostream &operator<<(std::ostream&, cat &a) {
	cout << "cat name is " << cat.name_ 
		<< "cat cata is " << cat.cata_
		<< "cat num is " << cat.num_;
}
std::ostream &operator<<(std::ostream&, elephent &a) {
	cout << "elephent name is " << elephent.name_ 
		<< "elephent cata is " << elephent.cata_
		<< "elephent num is " << elephent.num_;
}
dog* dog::add() {

}
