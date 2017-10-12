#include <stdlib.h>
#include <stdio.h>

extern int _sum(int x, int y);
extern int _mul(int x, int y);
extern int _div(int x, int y);
extern int _mod(int x, int y);
extern int _min(int x, int y);

int main()
{
	int x = 4;
	int y = 2;
	printf("%d %d\n", x, y);
	printf("sum:%d\n", _sum(x, y));
	printf("mul:%d\n", _mul(x, y));
	printf("sub:%d\n", _min(x, y));
	printf("mod:%d\n", _mod(x, y));
	printf("div:%d\n", _div(x, y));
	return 0;
}
