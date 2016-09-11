#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 15; 
int random (int N) { return rand()%N; }

main (){
	int i, j, A[N], flag=1, a=0, b=50;
    printf("\n Ishodniy massiv:\n");
    for (i=0; i<N; i++) {
        A[i] = random(b-a+1) + a;
        printf("%d  ",A[i]);
    }
    printf("\n Obrabotanniy massiv:\n%d  ", A[0]);
    for (i=1; i<N; i++) {
        for (j=0; j<i; j++)
            if (A[i]==A[j]) {
                flag=0;
                break;
            }
        if (flag)
            printf ("%d  ", A[i]);
        flag=1;
    }
	getch();
}
        
