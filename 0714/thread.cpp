#include "thread.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void thread::run(){
	while(1)
	{
		if(cha == 0){//producer
			this->p->push(rand()%100);	
			sleep(rand()%3);
		}else{//consumer
			this->p->pop();
			sleep(rand()%3);
		}
	}
}
