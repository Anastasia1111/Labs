#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctime>
const int N = 5;
int random (int N) { return rand()%N; }

main (){
    int a=0, b=10, i, j, A[N][N];
    srand ( time(NULL) );
	printf("\n Ishodnaya matrica:\n");
    for (i=0; i<N; i++) {               //���� �� �������
        for (j=0; j<N; j++) {           //���� �� ��������
            A[i][j] = random(b-a+1) + a;
            printf ("%3d", A[i][j]); 
        }
        printf("\n");
    }
    printf("\n Transponirovannaya matrica:\n");
    for (i=0; i<N; i++) {               //���� �� �������
        for (j=0; j<N; j++) {           //���� �� ��������
            printf ("%3d", A[j][i]); 
        }
        printf("\n");
    }
	getch();
}
        
