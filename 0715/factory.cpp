#include "factory.h"
void factory::run_thread_(){
	for(auto &item: Pros_){
		item.start();
	}
	for(auto &item: Cons_){
		item.start();
	}
	for(auto &item: Pros_){
		item.join();
	}
	for(auto &item: Cons_){
		item.join();
	}
}
