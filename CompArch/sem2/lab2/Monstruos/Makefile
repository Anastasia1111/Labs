all: clean matrix run
gdb: clean matrixgdb rungdb

matrix: matrix.cpp
	g++ -pthread -std=c++11 -o matrix matrix.cpp

clean:
	rm -rf *.o matrix matrixgdb

matrixgdb: matrix.cpp
	g++ -g -pthread -o matrixgdb matrix.cpp

rungdb: matrixgdb
	gdb matrixgdb

run: 
	./matrix 1130 2
	./matrix 1300 3
