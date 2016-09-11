#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 20; 
int random (int N) { return rand()%N; }

main (){
	int i, A[N], a=-10, b=10;
    for (i=0; i<N; i++) 
        A[i] = random(b-a+1) + a;
    printf("Polozhitel'nie:");
    for (i=0; i<N; i++){
        if (A[i]>=0) printf(" %d ",A[i]);
    }
    printf("\nOtricatel'nie:");
    for (i=0; i<N; i++){
        if (A[i]<0) printf(" %d ",A[i]);
    }
	getch();
}
        
