CC=gcc

CFLAGS=-c -Wall

all: clean chat

chat: chClient chServer

chServer: server.c
	$(CC) -pthread -o server server.c

chClient: client.c
	$(CC) -pthread -o client client.c

clean:
	rm -rf *.o 
