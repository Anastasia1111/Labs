#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 20; 
int random (int N) { return rand()%N; }

main (){
	int i, j, C[N],D[N],E[2*N], a=0, b=20, t;
    printf("\n Ishodniy massiv C:\n");
    for (i=0; i<N; i++) {
        C[i] = random(b-a+1) + a;
        printf("%d  ",C[i]);
    }
    printf("\n Ishodniy massiv D:\n");
    for (i=0; i<N; i++) {
        D[i] = random(b-a+1) + a;
        printf("%d  ",D[i]);
    }
    for (i=0; i<N-1; i++)
        for (j=N-2; j>=i; j--)
        if (C[j]>C[j+1]) {     
		    t=C[j]; 
            C[j]=C[j+1];
            C[j+1]=t;
        }
    for (i=0; i<N-1; i++)
        for (j=N-2; j>=i; j--)
        if (D[j]>D[j+1]) {     
		    t=D[j]; 
            D[j]=D[j+1];
            D[j+1]=t;
        }
    printf("\n Otsortirivanniy massiv C:\n");
    for (i=0; i<N; i++)
        printf("%d  ", C[i]);
    printf("\n Otsortirivanniy massiv D:\n");
    for (i=0; i<N; i++)
        printf("%d  ", D[i]);
    for (i=0,j=0,t=0; i<N;) {
        if (j<N&&C[i]>=D[j]) {
            E[t]=D[j];
            j++;
        } else {
            E[t]=C[i];
            i++;
        }
        t++;    
    }
    printf("\n Massiv E:\n");
    for (i=0; i<2*N; i++)
        printf("%d  ", E[i]);
	getch();
}
        
