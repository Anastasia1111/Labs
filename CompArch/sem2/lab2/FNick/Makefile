CC=g++

CFLAGS=-c -Wall

all: clean main
	./main 1750 1
	./main 1750 2
	./main 1750 3
	./main 2000 1
	./main 2000 2
	./main 2000 3
	./main 2250 1
	./main 2250 2
	./main 2250 3

main: main.o
	$(CC) -pthread main.o -o main

main.o: main.cpp
	$(CC) $(CFLAGS) -pthread main.cpp

clean:
	rm -rf *.o main
