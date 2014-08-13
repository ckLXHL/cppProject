.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test
OBJS=./tmp/Socket.o ./tmp/Rio.o ./tmp/TcpConnection.o ./tmp/PollPoller.o ./tmp/InetAddress.o ./tmp/TcpServer.o ./tmp/Thread.o ./tmp/Condition.o ./tmp/ThreadPool.o ./tmp/Exception.o ./tmp/Text.o ./tmp/correct.o ./tmp/Test.o ./tmp/Timer.o ./tmp/TimerThread.o
STARD=-std=c++0x
LINKS=-lpthread
INC=-I./include
./bin/$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(STARD) $(LINKS) $(INC)
./tmp/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD) $(INC)
clean:
	rm -rf ./tmp/*.o ./bin/$(BIN)
