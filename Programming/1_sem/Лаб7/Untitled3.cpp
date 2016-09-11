#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 20; 
int random (int N) { return rand()%N; }

main (){
	int i, j, a=-10, b=10, n;
	float A[N],B[N];
	printf("\n Ishodniy massiv:\n");
    for (i=0; i<N; i++) {
        A[i] = (float)rand()*(b-a)/RAND_MAX + a;
        if (A[i]>0) n++;
        printf("%5.1f \n",A[i]);
    }
    printf("\n Pobochniy massiv:\n");
    for (i=0; i<n; i++) {
    	for (j=0; j<N; j++) 
    	    if (A[j]>0) {
    	    	B[i]=A[j];
    	    	A[j]=-1;
    	    	break;
			}
		printf("%5.1f \n",B[i]);
	}
	getch();
}
        
