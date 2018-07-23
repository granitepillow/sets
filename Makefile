OBJS = card.o hand.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)


card.o: card.h card.cpp
	$(CC) $(CFLAGS) card.cpp

hand.o: card.h hand.h hand.cpp
	$(CC) $(CFLAGS) hand.cpp

sets_test: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) main.cpp -o sets_test

clean:
	rm *.o sets_test
