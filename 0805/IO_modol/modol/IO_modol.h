#ifndef IO_MODOL_H
#define IO_MODOL_H 

#include "NonCopyable.h"

class IO_modol : private NonCopyable {
	public:
		virtual ~IO_modol(){} ;
		virtual int IO_do_wait() = 0;
		virtual void IO_handle_accept() = 0;
		virtual void IO_handle_data(int) {};
		virtual void IO_handle_data() {};
};
#endif  /*IO_MODOL_H*/
