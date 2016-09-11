#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <ctime>
const int N = 3;
int random (int N) { return rand()%N; }

main (){
    int s, a=0, b=10, i, j, A[N][N], flag=1, k=0;
    srand (time(NULL));
    while (flag) {
       
	    for (i=0; i<N; i++)               //цикл по строкам
	        for (j=0; j<N; j++)           //цикл по столбцам
	            A[i][j] = random(b-a+1) + a;
	    s=A[0][0]+A[0][1]+A[0][2];
	    for (i=0; i<N; i++) {
	        if (A[i][0]+A[i][1]+A[i][2]==s) {if (A[0][i]+A[1][i]+A[2][i]==s) flag=0; else flag=1;} else flag=1;
			if (flag==1) break; 
		}
		k++;
    }
    printf("\n Poluchenniy kvadrat:\n");
    for (i=0; i<N; i++) {               //цикл по строкам
        for (j=0; j<N; j++) {           //цикл по столбцам
            printf ("%3d", A[i][j]); 
        }
        printf("\n");
    }
    printf("\n Kolichestvo generaciy: %d\n", k);
	getch();
}

        
