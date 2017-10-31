CC=gcc

CFLAGS=-c -Wall

all: clean UDP TCP

UDP: UDPserver UDPclient

UDPserver: UDPserver.o
	$(CC) UDPserver.o -o UDPserver

UDPserver.o: UDPserver.c
	$(CC) $(CFLAGS) UDPserver.c

UDPclient: UDPclient.o
	$(CC) UDPclient.o -o UDPclient

UDPclient.o: UDPclient.c
	$(CC) $(CFLAGS) UDPclient.c
	
TCP: TCPserver TCPclient

TCPserver: TCPserver.o
	$(CC) TCPserver.o -o TCPserver

TCPserver.o: TCPserver.c
	$(CC) $(CFLAGS) TCPserver.c

TCPclient: TCPclient.o
	$(CC) TCPclient.o -o TCPclient

TCPclient.o: TCPclient.c
	$(CC) $(CFLAGS) TCPclient.c

clean:
	rm -rf *.o UDP TCP
