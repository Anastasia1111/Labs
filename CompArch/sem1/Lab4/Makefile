main: clear main.o libMyBigChars.a
	gcc -o main main.o -L. -lMyBigChars

main.o: main.c
	gcc -c main.c

libMyBigChars.a: myBigChars.o myTerm.o
	ar rc libMyBigChars.a myBigChars.o myTerm.o

myBigChars.o: myBigChars.c
	gcc -c myBigChars.c

myTerm.o: myTerm.c
	gcc -c myTerm.c

clear:
	rm -f *.o *.a
