#include <math.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int start = clock();
	int res;
	double a = 2.3;
	for(int i = 0; i < 1000000; ++i)
	{
		asm
		(
			"FTOSID s1, s2\n\t"
			: "s1" (res)
			: "s2" (a)
		);
	}
	printf("%i\n", res);
	int end = clock();
	printf("runtime = %ims\n", end - start);
	return 0;
}
