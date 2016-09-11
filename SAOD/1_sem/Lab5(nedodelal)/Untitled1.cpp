#include "bible4.cpp"

void BSearch1(int* A, int n, int key)
{
     int m,L=1,R=n-1;
     bool done=0;
     while (L<=R) {
           m=(L+R)/2;
           if (A[m]==key) { done=1; break; }
           if (A[m]<key) L=m+1;
           else R=m-1;
     }
     printf("Element, that you are looking for: %d\n",m+1);
}

main() {
       int *A, n, i, key;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       A=new int [n];
       if (A==NULL){
           printf(" ERROR ");
           return 1;
       }
       FillRand(A, n);
       //FillInc(A, n);
       //FillDec(A, n);
       Output(A, n); //Вывод исходного массива
       printf("\nSorted:");
       ShellSort(A, n);
       Output(A, n); //Вывод отсортированного массива
       printf("\nType the key: ");
       scanf("%d",&key);
       BSearch1(A, n, key);
       delete A;
       A=NULL;
       system("Pause");
       return 0;
}
