CC=g++

CFLAGS=-c -Wall

all: lab1-1 lab1-2 lab1-3

lab1-1: lab1-12.o
	$(CC) -O0 lab1-12.o -o lab1-1

lab1-2: lab1-12.o
	$(CC) -O3 lab1-12.o -o lab1-2

lab1-3: lab1-3.o
	$(CC) lab1-3.o -o lab1-3

lab1-12.o: lab1-12.cpp
	$(CC) $(CFLAGS) lab1-12.cpp

lab1-3.o: lab1-3.cpp
	$(CC) $(CFLAGS) lab1-3.cpp

clean:
	rm -rf *.o lab1-1 lab1-2 lab1-3
