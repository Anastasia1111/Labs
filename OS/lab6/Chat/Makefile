CC=gcc

CFLAGS=-c -Wall

all: clean chat

chat: chClient chServer

chServer: TCPsch.c
	$(CC) -pthread -o TCPsch TCPsch.c

chClient: TCPcch.c
	$(CC) -pthread -o TCPcch TCPcch.c

clean:
	rm -rf *.o 
