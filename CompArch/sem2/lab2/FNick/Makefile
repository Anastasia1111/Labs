CC=g++

CFLAGS=-c -Wall

all: clean main
	./main 3 2

main: main.o
	$(CC) -pthread main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -pthread main.cpp

clean:
	rm -rf *.o main
