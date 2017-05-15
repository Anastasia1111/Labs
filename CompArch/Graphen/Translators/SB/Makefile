#Makefile for translatorB

SRC = SBT.c error_logB.c Btranslate.c input.c RPN.c goto.c if.c end.c
OBJ = $(SRC:.c=.o)

.PHONY: all sbt clean

all: clean sbt

sbt:
	gcc -g -I../../headers $(SRC) -o sbt -L../../lib -lSimpleComputer
	
clean:
	rm -rf *.o
