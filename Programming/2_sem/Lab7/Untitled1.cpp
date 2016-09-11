#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int N1=10;
const int N2=15;

void sort(int a[], int N) {
    int i, j, tmp, max;
    for (i=0; i<N-1; i++) {
        max=i;
        for (j=i+1; j<N; j++)
            if (a[max]<a[j]) max=j;
        tmp=a[i]; a[i]=a[max]; a[max]=tmp;
    }
}

main() {
    int A[N1], B[N2], i;
    srand(time(0));
	printf("Isshodnie massivi\nA: ");
	for(i=0; i<N1; i++) { A[i]=rand()%N1+1; printf("%d ",A[i]); }  		
    printf("\nB: ");
    for(i=0; i<N2; i++) { B[i]=rand()%N2+1; printf("%d ",B[i]); }  						
    sort(A,N1); sort(B,N2);
    printf ("\nOtsortirovannie massivi\nA: ");
    for(i=0; i<N1; i++) printf("%d ",A[i]);
    printf("\nB: ");
    for(i=0; i<N2; i++) printf("%d ",B[i]);
    printf("\n");       
   system("Pause");
}
