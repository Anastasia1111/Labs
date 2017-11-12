CC=g++

CFLAGS=-c -Wall

all: clean main
	./main

main: main.o
	$(CC) -pthread main4.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -pthread main4.cpp

clean:
	rm -rf *.o main
