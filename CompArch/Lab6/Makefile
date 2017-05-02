#Makefile

main: clear hdchs.a main.o
	gcc -o main main.o -L. -lhdchs

hdchs.a: hdchs.o
	ar rc libhdchs.a hdchs.o

hschs.o: hdchs.c
	gcc -c hdchs.c

main.o: main.c
	gcc -c main.c

clear: 
	rm -rf *.a *.o
