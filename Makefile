.PHONY:clean
CC=g++
CFLAGS=-Wall -g
BIN=test_queue
OBJS=Queue.o test_main.o
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN)
