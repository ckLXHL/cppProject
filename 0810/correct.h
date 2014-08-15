#ifndef CORRECT_H
#define CORRECT_H 

#include "Text.h"
#include "TimerThread.h"
#include "TcpServer.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "ThreadPool.h"
class correct 
{
	public:
		correct();		
		void start();
	private:
		void setFunc();
		//设定函数
		void HandleRequest(const TcpConnectionPtr&, const std::string&);
		void onConnection(const TcpConnectionPtr&);
		void onMessage(const TcpConnectionPtr&);
		void onClose(const TcpConnectionPtr&);
		//变量
		InetAddress netAddress_;
		TcpServer server_;
		Text txt_;
		TimerThread timeThread_;
		ThreadPool threads_;
};
#endif  /*correct.h*/
