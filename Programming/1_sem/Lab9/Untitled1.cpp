#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int M = 10; //число строк
const int N = 20; //число столбцов
int random (int N) { return rand()%N; }

main (){
    int tmp, a=0, b=50, i, j, A[M][N];
    printf("\n Ishodniy massiv:\n");
    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            A[i][j] = random(b-a+1) + a;
            printf ("%3d", A[i][j]); // подсказка для ввода
        }
        printf("\n"); // переход на другую строку
    }
    for (i=0; i<M; i+=2) {
        for (j=0; j<N; j++) {
            tmp = A[i][j];
            A[i][j] = A[i+1][j];
            A[i+1][j] = tmp;
        }
    }
    printf("\n Izmenoynniy massiv:\n");
    for (i=0; i<M; i++) {
        for (j=0; j<N; j++) {
            printf ("%3d", A[i][j]); // подсказка для ввода
        }
        printf("\n"); // переход на другую строку
    }
	getch();
}
        
