#include <cmath>
#include <time.h>
#include <limits.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	int start = clock();
    for (int i=0; i<INT_MAX/100; ++i){
		float f1 = i*1.0;
		float f2 = i*1.5;
		f1 = fmin(f1, f2);
	}
	int end = clock();
	printf("%d ms\n", end - start);
    return 0;
};
