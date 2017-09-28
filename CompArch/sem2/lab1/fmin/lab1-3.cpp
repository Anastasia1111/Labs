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
		asm ("FCMPS s1, s2\n\t"
		     "FMSTAT\n\t"
		     "FCPYSGT s1, s2\n\t"
		     : "s1" (f1)
		     : "s2" (f2));
	}
	int end = clock();
	printf("%d ms\n", end - start);
    return 0;
};
