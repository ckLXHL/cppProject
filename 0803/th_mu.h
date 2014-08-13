#include <pthread.h>
class th_mu{
	public:
		th_mu(){
			if(pthread_mutex_init(&mt, NULL))
				throw std::runtime_error("mutex init fail");
		}
		~th_mu(){
			if(pthread_mutex_destroy(&mt))
				throw std::runtime_error("mutex des fail");
		}
		void lock(){
			pthread_mutex_lock(&mt);
		}
		pthread_mutex_t& getlock(){
			return mt;
		}
		void unlock(){
			pthread_mutex_unlock(&mt);
		}
	private:
		pthread_mutex_t mt;
};
