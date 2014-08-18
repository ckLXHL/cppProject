#include "correct.h"
#include <functional>
correct::correct():netAddress_(8989),
				   server_(netAddress_),
				   txt_("./dictionary"),
				   timeThread_(),
				   threads_(5, 5),
				   cacMan_(5)
{
	setFunc();
}


void correct::setFunc()
{
	timeThread_.setTimerCallback(std::bind(&cacheManager::writeToFile, &cacMan_));
	timeThread_.setTimer(60, 60);
	threads_.start();
	server_.setConnection(std::bind(&correct::onConnection, this, std::placeholders::_1));
	server_.setMessage(std::bind(&correct::onMessage, this, std::placeholders::_1));
	server_.setClose(std::bind(&correct::onClose, this, std::placeholders::_1));
	txt_.print();
}

void correct::onConnection(const TcpConnectionPtr &conn)
{
	conn->send("Welcome to server\r\n");	
}
void correct::onMessage(const TcpConnectionPtr &conn)
{
	std::string st = conn->receive();
	while(*st.rbegin() == '\r' || *st.rbegin() == '\n')
		st.resize(st.size() - 1);
	threads_.addTask(bind(&correct::HandleRequest, this, conn, st)); 
}
void correct::HandleRequest(const TcpConnectionPtr &conn, const std::string &st)
{
	if (txt_.Match(st)) {
		conn->send(std::string("find:\n") + st + "\r\n");
		std::cout << "find " << st << std::endl;
	}
	else {
		cache& cac= cacMan_.goCache();
		std::string answer = cac.isExist(st);
		if (answer == "") {
			answer == txt_.calMatch(st);
			cac.add(st, answer);
		}
		conn->send(std::string("no find\nsuggestion:\n") + answer + "\r\n");
		std::cout << "no find " << st <<std::endl;
		cac.deHold();
	}
}
void correct::onClose(const TcpConnectionPtr&) 
{
	std::cout << "Connection Close!" << std::endl;
}
void correct::start()
{
	timeThread_.startTimerThread();
	server_.start();
	threads_.start();
}
