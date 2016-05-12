#include "bible.cpp"

const int n=10;
int A[n];
const int M=3*(n-1);
const int C=(n*n-n)/2;

void SelectSort(int* A, int n)
{
     int i,j,k,t;
     for (i=0; i<n-1; i++) {
         k=i;
         for (j=i+1; j<n; j++) {
             if (A[j]<A[k]) k=j;
         }
         t=A[k]; A[k]=A[i]; A[i]=t; 
     }
}

main() {
       int i, chsum, rnum;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       FillRand(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       printf("\nAverage RN: %4.1f\n", (float)n/rnum);
       printf("\nSorted:");
       SelectSort(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       printf("\nAverage RN: %4.1f\n", (float)n/rnum);
       system("Pause");
       return 0;
}

