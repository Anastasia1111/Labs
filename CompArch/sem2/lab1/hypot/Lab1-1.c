#include <math.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int start = clock();
	int res;
	for(int i = 0; i < 1000000; ++i)
	{
		int a = 3, b = 4;
		asm
		(
			"imul %1, %1\n\t"
			"imul %2, %2\n\t"
			"add %2, %1\n\t"
			"mov %0, %2\n\t"
			:"=r"(res)
			:"r"(a),
			"r"(b)
		);
	}
	printf("%i\n", res);
	int end = clock();
	printf("runtime = %ims\n", end - start);
	return 0;
}
