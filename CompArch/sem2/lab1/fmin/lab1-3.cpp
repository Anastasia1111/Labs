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
		float res;
		asm (
			"FCMPS %[f1], %[f2]\n\t"
		     	"FMSTAT\n\t"
			"FCPYS %[res], %[f1]\n\t"
			"BLS .END\n\t"
		     	"FCPYS %[res], %[f2]\n\t"
			".END:\n\t"
		     	: [res] "=w" (res)
		     	: [f1] "w" (f1)
			, [f2] "w" (f2)
		);
	}
	int end = clock();
	printf("%d ms\n", end - start);
    return 0;
};
