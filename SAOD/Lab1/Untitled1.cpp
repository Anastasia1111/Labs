#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <time.h>

void FillInc(int* A, int n)
{
      int i;
      for (i=0; i<n; i++) A[i]=i+1;
}

void FillDec(int* A, int n)
{
      int i;
      for (i=0; i<n; i++) A[i]=n-i;
}

void FillRand(int* A, int n)
{
      int i;
      srand(time(0));
      for (i=0; i<n; i++) A[i]=rand()%(2*n+1)-n;
}

int CheckSum(int* A, int n)
{
      int i, cs=0;
      for (i=0; i<n; i++) cs+=A[i];
      return cs;
}

int RunNumber(int* A, int n)
{
      int i, rn=1;
      for (i=1; i<n; i++)
          if (A[i-1]>A[i]) rn++;
      return rn;
}

void PrintMas(int* A, int n)
{
     int i;
     printf("\nMassiv: ");
     for (i=0;i<n;i++) printf("%d ",A[i]);
}

main() {
       int *A, n, i, chsum, rnum;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       A=new int [n];
       if (A==NULL){
           printf(" ERROR ");
           return 1;
       }
       FillInc(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       FillDec(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       FillRand(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       printf("\nAverage RN: %4.1f\n", (float)n/rnum);
       delete A;
       A=NULL;
       system("Pause");
       return 0;
}
