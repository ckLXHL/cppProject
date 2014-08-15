#include <iostream>
#include <pthread.h>
#include <stdlib.h>
using namespace std;
class Singleton {
	public:
		static Singleton *getInstance() {
			pthread_once(&once_, initInstance);
			return pInstance_;
		}
		static void initInstance() {
		::atexit(&destroyInstance);
		pInstance_ = new Singleton;
		}
		static void destroyInstance() {
			cout << "destroy" << endl;
			delete pInstance_;
		}
	private:
		Singleton() {};
		Singleton(const Singleton &);
		void operator=(const Singleton &);
		static Singleton *pInstance_;
		static pthread_once_t once_;
};
Singleton *Singleton::pInstance_ = NULL;
pthread_once_t Singleton::once_ = p
