main: clear main2.o libMyBigChars.a
	gcc -o main2 main2.o -L. -lMyBigChars -lSimpleComputer

main2.o: main2.c
	gcc -c main2.c

libMyBigChars.a: myBigChars.o myTerm.o
	ar rc libMyBigChars.a myBigChars.o myTerm.o

myBigChars.o: myBigChars.c
	gcc -c myBigChars.c

myTerm.o: myTerm.c
	gcc -c myTerm.c

clear:
	rm -f *.o libMyBigChars.a
