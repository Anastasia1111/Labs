#include "bible2.cpp"

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

void BubbleSortMC(int* A, int n)
{
     int i,j,t,m,c;
     m=c=0;
     for (i=0; i<n; i++) {
         for (j=n-1; j>i; j--) {
             c++;
             if (A[j]<A[j-1]) {t=A[j]; m++; A[j]=A[j-1]; m++; A[j-1]=t; m++;}
         }
     }
     printf("\nPractical M and C:\nM=%d C=%d",m,c);
}

void ShakerSortMC(int* A, int n)
{
     int i,j,t,l=0,r=n-1,k=n-1,m,c;
     m=c=0;
     while (l<r) {
           for (j=r; j>l; j--) {
               c++;
               if (A[j]<A[j-1]) {t=A[j]; m++; A[j]=A[j-1]; m++; A[j-1]=t; m++; k=j;}
           }
           l=k;
           for (j=l; j<r; j++) {
               c++;
               if (A[j]>A[j+1]) {t=A[j]; m++; A[j]=A[j+1]; m++; A[j+1]=t; m++; k=j;}
           }
           r=k;
     }
     printf("\nPractical M and C:\nM=%d C=%d",m,c);
}

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
       c=(n*n-n)/2; m=3*c/2; //Для рандома и шейкера
       //c=(n*n-n)/2; m=0; //Для возрастания
       //c=(n*n-n)/2; m=3*c; //Для убывания
       printf("\nTheoretical M and C:\nM=%d C=%d\n",m,c); //Для "пузырька"
       FillRand(A, n);
       //FillInc(A, n);
       //FillDec(A, n);
       PrintMas(A, n);
       chsum=CheckSum(A, n);
       printf("\nCheck Summ: %d", chsum);
       rnum=RunNumber(A, n);
       printf("\nRun Number: %d", rnum);
       printf("\nAverage RN: %4.1f\n", (float)n/rnum);
       printf("\nSorted:");
       //BubbleSort(A, n);
       //ShakerSort(A, n);
       //BubbleSortMC(A, n);
       ShakerSortMC(A, n);
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

