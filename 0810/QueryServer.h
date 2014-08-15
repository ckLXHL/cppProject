#ifndef QUERYSERVER_H
#define QUERYSERVER_H 
#include <NonCopyable>
#include <TcpServer>
#include "ThreadPool.h"
class QueryServer: private NonCopyable {
	public:
	private:
		TcpServer TcpSer;
		ThreadPool ThP;
}
#endif  /*QUERYSERVER_H*/
