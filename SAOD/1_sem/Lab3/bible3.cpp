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

void SelectSort(int* A, int n)
{
     int i,j,k,t;
     for (i=0; i<n-1; i++) {
         k=i;
         for (j=i+1; j<n; j++) {
             if (A[j]<A[k]) k=j;
         }
         if (i<k) {t=A[k]; A[k]=A[i]; A[i]=t;}
     }
}

void BubbleSort(int* A, int n)
{
     int i,j,t;
     for (i=0; i<n; i++) {
         for (j=n-1; j>i; j--) {
             if (A[j]<A[j-1]) {t=A[j]; A[j]=A[j-1]; A[j-1]=t;}
         }
     }
}

void ShakerSort(int* A, int n)
{
     int i,j,t,l=0,r=n-1,k=n-1;
     while (l<r) {
           for (j=r; j>l; j--) {
               if (A[j]<A[j-1]) {t=A[j]; A[j]=A[j-1]; A[j-1]=t; k=j;}
           }
           l=k;
           for (j=l; j<r; j++) {
               if (A[j]>A[j+1]) {t=A[j]; A[j]=A[j+1]; A[j+1]=t; k=j;}
           }
           r=k;
     }
}

void Output(int *A, int n)
{
     int chsum, rnum;
     PrintMas(A, n);
     chsum=CheckSum(A, n);
     printf("\nCheck Summ: %d", chsum);
     rnum=RunNumber(A, n);
     printf("\nRun Number: %d", rnum);
     printf("\nAverage RN: %4.1f\n", (float)n/rnum);
}
