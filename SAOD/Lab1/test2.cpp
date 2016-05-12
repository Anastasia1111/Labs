#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
const int N=15;

void FillInc(int* A, int n)
{
      int i;
      for (i=0; i<n; i++) A[i]=N-i;
}

main() {
       int A[N], i;
       FillInc(A, N);
       printf("Massiv: ");
       for (i=0;i<N;i++) printf("%d ",A[i]);
       system("Pause");
       return 0;
}
