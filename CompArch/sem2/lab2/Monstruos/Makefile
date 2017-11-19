all: clean matrix run
gdb: clean matrixgdb rungdb

matrix: matrix.cpp
	g++ -pthread -o matrix matrix.cpp

clean:
	rm -rf *.o matrix matrixgdb

matrixgdb: matrix.cpp
	g++ -g -pthread -o matrixgdb matrix.cpp

rungdb: matrixgdb
	gdb matrixgdb

run: 
	./matrix 500 1
	./matrix 500 2
	./matrix 500 3
	./matrix 500 4
	./matrix 500 5
	./matrix 500 6
	./matrix 500 7
	./matrix 500 8
	./matrix 1000 1
	./matrix 1000 2
	./matrix 1000 3
	./matrix 1000 4
	./matrix 1000 5
	./matrix 1000 6
	./matrix 1000 7
	./matrix 1000 8
	./matrix 1500 1
	./matrix 1500 2
	./matrix 1500 3
	./matrix 1500 4
	./matrix 1500 5
	./matrix 1500 6
	./matrix 1500 7
	./matrix 1500 8
	./matrix 2000 1
	./matrix 2000 2
	./matrix 2000 3
	./matrix 2000 4
	./matrix 2000 5
	./matrix 2000 6
	./matrix 2000 7
	./matrix 2000 8