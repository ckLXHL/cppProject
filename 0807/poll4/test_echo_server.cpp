#include "TcpServer.h"
#include "NonCopyable.h"
#include <iostream>
#include <string>
using namespace std;
using namespace std::placeholders;

class EchoServer : NonCopyable
{
    public:
        EchoServer(const InetAddress &addr, int a, int b)
            :server_(addr, a, b)
        {
            server_.setConnection(bind(&EchoServer::onConnect, this, _1));
            server_.setMessage(bind(&EchoServer::onMessage, this, _1));
        }

        void start()
        {
            server_.start();
        }

                
    private:
        void onConnect(const TcpConnectionPtr &conn)
        {
            conn->send("hello\r\n");
            conn->send("the TCP Connection will be closed!\r\n");
        }

        void onMessage(const TcpConnectionPtr &conn)
        {
            cout << "recv data" << conn->receive();
            conn->send("ACK\r\n");
        }

        TcpServer server_;
};


int main(int argc, const char *argv[])
{
    InetAddress addr(8989);
    EchoServer server(addr, 3, 3);
    server.start();
    return 0;
}


