#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
const int N=100; // Размер последовательности

void vivod(int *p, int i)
{
    if (p[i]) {
        if (p[i]<0) printf("%d ",p[i]);
        vivod(p,i+1);
        if (p[i]>0) printf("%d ",p[i]);
    }
}

main() {
    int i, A[N];
	printf("Vvedite posledovatelnost chisel: \n");
	for(i=0; i<N; i++) { scanf("%d", &A[i]); if (!A[i]) break; } 
	vivod(A,0);
    getch(); 
}
