main: clear main2.o
	gcc -o main main2.o -Llib -lMyBigChars -lSimpleComputer -lMyTerm -lMyReadKey 

main2.o: main2.c
	gcc -c main2.c

clear:
	rm -f *.o
