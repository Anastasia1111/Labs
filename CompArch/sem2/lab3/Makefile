CC=mpic++

all: clean main
	mpirun -n 5 ./main 1750

main: main.cpp
	$(CC) -o main main.c

clean:
	rm -rf *.o main
