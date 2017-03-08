#Makefile

main: clean main.o libMyTerm.a
	gcc -o main main.o -L. -lMyTerm

main.o: main.c
	gcc -c main.c

libMyTerm.a: myTerm.o
	ar rc libMyTerm.a myTerm.o

myTerm.o: myTerm.c
	gcc -c myTerm.c

clean:
	rm -f *.o *.a
