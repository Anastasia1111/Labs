#Makefile for translator

SRC = SAT.c error_log.c translate.c
OBJ = $(SRC:.c=.o)

.PHONY: all sat clean

all: clean sat

sat:
	gcc -I../headers $(SRC) -o sat -L../lib -lSimpleComputer
	
clean:
	rm -rf *.o
