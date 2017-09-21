main: clear main2.o SimpleComputer.o ALUCU.o
	gcc -o main main2.o SimpleComputer.o ALUCU.o -Llib -lMyBigChars -lSimpleComputer -lMyTerm -lMyReadKey 

main2.o: main2.c
	gcc -c main2.c

SimpleComputer.o:
	gcc -c SimpleComputer.c
	
ALUCU.o:
	gcc -c ALUCU.c

clear:
	rm -f *.o
