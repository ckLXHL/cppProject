.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test
OBJS=./tmp/Socket.o ./tmp/Rio.o ./tmp/TcpConnection.o ./tmp/PollPoller.o ./tmp/InetAddress.o ./tmp/TcpServer.o ./tmp/Thread.o ./tmp/Condition.o ./tmp/ThreadPool.o ./tmp/Exception.o ./tmp/handle.o ./tmp/Test.o ./tmp/Timer.o ./tmp/TimerThread.o ./tmp/correct.o ./tmp/cache.o ./tmp/cacheManager.o ./tmp/Text.o
STARD=-std=c++0x
LINKS=-lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(STARD) $(LINKS) $(INC)
./tmp/%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(STARD) $(INC)
clean:
	rm -rf ./tmp/*.o ./bin/$(BIN)
