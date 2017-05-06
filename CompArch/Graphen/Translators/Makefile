#Makefile for translator

SRC = SAT.c error_log.c translate.c
OBJ = $(SRC:.c=.o)

.PHONY: all sat clean

all: clean sat

sat:
	gcc $(SRC) -o sat
	
clean:
	rm -rf *.o
