#include <math.h>
#include <stdio.h>
#include <time.h>

int main()
{
	int start = clock();
	for(int i = 0; i < 1000000; ++i)
		floor(0.4);
	int end = clock();
	printf("runtime = %ims\n", end - start);
	return 0;
}
