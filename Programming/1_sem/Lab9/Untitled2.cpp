#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 5;
int random (int N) { return rand()%N; }

main (){
    int a=0, b=10, i, j, s;
    float A[N][N], B[N][N];
    printf("\n Ishodniy massiv:\n");
    for (i=0; i<N; i++) {               //цикл по строкам
        for (j=0; j<N; j++) {           //цикл по столбцам
            A[i][j] = random(b-a+1) + a;
            printf ("%7.3f", A[i][j]); 
            s+=A[i][j];
        }
		for (j=0; j<N; j++) B[i][j] = A[i][j]/s;
		s=0;
        printf("\n");
    }
    printf("\n Izmenoynniy massiv:\n");
    for (i=0; i<N; i++) {               //цикл по строкам
        for (j=0; j<N; j++) {           //цикл по столбцам
            printf ("%7.3f", B[i][j]); 
        }
        printf("\n");
    }
	getch();
}
        
