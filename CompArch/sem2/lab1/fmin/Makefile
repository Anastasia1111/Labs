CC=g++

CFLAGS=-c -Wall

all: lab1-1 lab1-2 lab1-3 asm

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
	
asm: asm1 asm2 asm3
	
asm1:
	$(CC) -S -O0 lab1-12.cpp -o asm1.ass
	
asm2:
	$(CC) -S -O3 lab1-12.cpp -o asm2.ass
	
asm3:
	$(CC) -S lab1-3.cpp -o asm3.ass

clean:
	rm -rf *.o *.ass lab1-1 lab1-2 lab1-3
