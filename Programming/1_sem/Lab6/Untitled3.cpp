#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 20; 
int random (int N) { return rand()%N; }

main (){
	int i, a=0, b=10;
	float A[N];
    for (i=0; i<N; i++) 
        A[i] = (float)rand()*(b-a)/RAND_MAX + a;
    printf("\nVivod elementov massiva:\n");     
    for (i=0; i<N; i++)
        printf("%6.2f",A[i]);
    printf("\nVivod <<bol'shih>> chisel:\n");
    for (i=1; i<N; i++) {
        if (A[i]>A[i-1]&&A[i]>A[i+1]) printf("%6.2f",A[i]);
    }
	getch();
}
        
