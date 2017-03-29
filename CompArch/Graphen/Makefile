main: clear main2.o
	gcc -o main main2.o -L. -lMyBigChars -lSimpleComputer -lMyTerm -lMyReadKey 

main2.o: main2.c
	gcc -c main2.c

clear:
	rm -f *.o
