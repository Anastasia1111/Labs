#Makefile

main: main.o libSimpleComputer.a
	gcc -o main main.o -L. -lSimpleComputer
	echo main is ready!

main.o: main.c
	gcc -c main.c

libSimpleComputer.a: sc.o
	ar r libSimpleComputer.a sc.o

sc.o: sc.c
	gcc -c sc.c

clean:
	rm -f *.o
	echo Clean
