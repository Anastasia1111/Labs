#include "bible2.cpp"

void SelectSortMC(int* A, int n)
{
     int i,j,k,t,m,c;
     m=c=0;
     for (i=0; i<n-1; i++) {
         k=i;
         for (j=i+1; j<n; j++) {
             c++;
             if (A[j]<A[k]) k=j;
         }
         t=A[k]; m++; A[k]=A[i]; m++; A[i]=t; m++;
     }
     printf("\nPractical M and C:\nM=%d C=%d",m,c);
}

void SelectSortMCImp(int* A, int n)
{
     int i,j,k,t,m,c;
     m=c=0;
     for (i=0; i<n-1; i++) {
         k=i;
         for (j=i+1; j<n; j++) {
             c++;
             if (A[j]<A[k]) k=j;
         }
         if (i<k) { t=A[k]; m++; A[k]=A[i]; m++; A[i]=t; m++; }
     }
     printf("\nPractical M and C:\nM=%d C=%d",m,c);
}

main() {
       int *A, n, i, chsum, rnum, m, c;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       A=new int [n];
       if (A==NULL){
           printf(" ERROR ");
           return 1;
       }
       m=3*(n-1); c=(n*n-n)/2;
       printf("\nTheoretical M and C:\nM=%d C=%d\n",m,c);
       //FillRand(A, n);
       FillInc(A, n);
       //FillDec(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       printf("\nAverage RN: %4.1f\n", (float)n/rnum);
       printf("\nSorted:");
       //SelectSort(A, n);
       SelectSortMC(A, n);
       //SelectSortMCImp(A, n);
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

