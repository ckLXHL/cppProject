#include "thread.h"
int add(int a, int b, int c){};
int main() {
	thread_pool tp(10, print);
	tp.pool_start();
	std::function<int ()> p2(print);
	std::function<int (int, int ,int)> p3(add);
	printf("%d %d\n", sizeof p2, sizeof p3);
}
