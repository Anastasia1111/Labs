#include "bible.cpp"

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
