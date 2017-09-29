#include <math.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int start = clock();
	double x;
	for(int i = 0; i < 1000000; ++i)
		x = 2.3
		floor(x);
	int end = clock();
	printf("runtime = %ims\n", end - start);
	return 0;
}
