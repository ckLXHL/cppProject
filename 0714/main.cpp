#include <pthread.h>
#include <unistd.h>
#include "thread.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main(){
	my_queue<int> q;
	thread p1(0, &q);
	p1.start();
	thread p2(1, &q);
	p2.start();
	thread p3(0, &q);
	p3.start();
	p1.join();
	p2.join();
	p3.join();
	return 0;
}	

