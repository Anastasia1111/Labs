main: clear main2.o SimpleComputer.o
	gcc -o main main2.o SimpleComputer.o -Llib -lMyBigChars -lSimpleComputer -lMyTerm -lMyReadKey 

main2.o: main2.c
	gcc -c main2.c

SimpleComputer.o:
	gcc -c SimpleComputer.c

clear:
	rm -f *.o
