#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

void FillInc(int* A, int n)
{
      int i;
      for (i=0; i<n; i++) A[i]=n-i;
}

main() {
       int *A, n, i;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       A=new int [n];
       if (A==NULL){
           printf(" ERROR ");
           return 1;
       }
       FillInc(A, n);
       printf("Massiv: ");
       for (i=0;i<n;i++) printf("%d ",A[i]);
       delete A;
       A=NULL;
       system("Pause");
       return 0;
}
