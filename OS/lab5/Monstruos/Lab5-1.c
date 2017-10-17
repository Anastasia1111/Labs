#include <stdlib.h>
#include <stdio.h>
extern int add(int a, int b);
extern int divis(int a, int b);
extern int sub(int a, int b);
extern int multi(int a, int b);
extern int rem_of_div(int a, int b);

int main(int argc, char const *argv[])
{
	printf("%d", add(2, 3));
	printf("%d", sub(2, 3));
	printf("%d", divis(2, 3));
	printf("%d", multi(2, 3));
	printf("%d", rem_of_div(2, 3));
	return 0;
}