#ifndef TH_CO_H
#define TH_CO_H 
#include <stdexcept>
class th_co{
	public:
		th_co(){
			if(pthread_cond_init(&ct, NULL))
				throw std::runtime_error("cond init fail");
		}
		virtual ~th_co(){
			if(pthread_cond_destroy(&ct))
				throw std::runtime_error("cond des fail");
		}
		void wait(pthread_mutex_t& mu){
			if(pthread_cond_wait(&ct, &mu))
				throw std::runtime_error("con wait fail");
		}
		void sig(){
			pthread_cond_signal(&ct);
		}
	private:
		pthread_cond_t ct;
};
#endif  /*TH_CO_H*/
