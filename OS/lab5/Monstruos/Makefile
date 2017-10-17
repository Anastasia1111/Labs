SRC = add.c sub.c multi.c div.c rem_of_div.c
OBJ = $(SRC:.c=.o)
SOBJ = $(patsubst %.o,lib%.so,$(OBJ))
LIBSNAME = $(patsubst %.o,-l%,$(OBJ))

all: clean res clean_obj

echo:
	echo $(SOBJ)'\n' & echo $(OBJ)'\n' & echo $(LIBSNAME)'\n'
clean:
	rm -rf *.o *.so *.out
obj: $(SRC) 
	gcc -fPIC -c $(SRC)
so: obj
	gcc -shared -o libadd.so add.c
	gcc -shared -o libsub.so sub.c
	gcc -shared -o libmulti.so multi.c
	gcc -shared -o libdiv.so div.c
	gcc -shared -o librem_of_div.so rem_of_div.c
5-1.o: Lab5-1.c
	gcc -c Lab5-1.c
5-2.o: Lab5-2.c
	gcc -c Lab5-2.c
5-3.o: Lab5-3.c
	gcc -c Lab5-3.c
res: so 5-1.o 5-2.o 5-3.o
	gcc -o a1.out Lab5-1.o -L. $(LIBSNAME)
	gcc -o a2.out Lab5-2.o
	gcc -o a3.out Lab5-3.o
clean_obj:
	rm -rf *.o