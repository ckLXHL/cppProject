#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include "factory.h"
using namespace std;
int main(){
	factory fac(5, 2, 2);
	fac.run_thread_();
	return 0;
}

