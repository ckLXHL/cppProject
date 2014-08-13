.PHONY:clean
CC=g++
CFLAGS=-Wall -g -std=c++0x -lpthread
BIN=main
D=./tmp
HEADER=factory.h th_co.h buffer.h thread.h safe_queue.h th_mu.h
OBJS=buffer.o main.o factory.o thread.o
%.o:%.cpp %.h
	mkdir $(D);\
		$(CC) -c $< -o $(D)/$@ $(CFLAGS);
		

$(BIN):$(D)/$(OBJS) $(HEADER)
	$(CC) $^ -o $@ $(CFLAGS); \
		rm -f *.o
clean:
	rm -f *.o $(BIN)
