#include "thread.h"
/*void thread::run(){
	while(1)
	{
		if(cha == 0){//producer
			buf.Produce(rand()%100);
			std::cout << "produce a item ,now we have " << buf.Get_Size() << std::endl;
			sleep(rand()%3);
		}else{//consumer
			buf.Consum();
			std::cout << "consum a item ,now we have " << buf.Get_Size() << std::endl;
			sleep(rand()%3);
		}
	}
}*/
void Consum_Thread::run(){
	while(1)
	{//consumer
		buf_.Consum();
		std::cout << "produce a item ,now we have " << buf_.Get_Size() << std::endl;
		sleep(rand()%3);
	}
}
void Produc_Thread::run(){
	while(1)
	{//producer
		buf_.Produce(rand()%100);
		std::cout << "consum a item ,now we have " << buf_.Get_Size() << std::endl;
		sleep(rand()%3);
	}
	
}
