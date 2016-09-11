#include "bible3.cpp"

void InsertSort(int* A, int n)
{
     int i,j,t;
     for (i=1; i<n; i++) {
         t=A[i]; //��� ���������
         for (j=i-1; (j>=0)&&(t<A[j]); j--) A[j+1]=A[j]; //��� ��������� � ���������
         A[j+1]=t; //��� ���������
     }
}

void InsertSortMC(int* A, int n)
{
     int i,j,t,m=0,c=0;
     for (i=1; i<n; i++) {
         t=A[i]; m++; //��� ���������
         c++;
         for (j=i-1; (j>=0)&&(t<A[j]); j--) { A[j+1]=A[j]; c++; m++; } //��� ��������� � ���������
         A[j+1]=t; m++; //��� ���������
     }
     printf("\nPractical M and C:\nM=%d C=%d",m,c);
}

void ShellSort(int* A, int n)
{
     int i,j,t,k,m,l,*h;
     //���������� ������� �����
     m=(int)(log10(n)/log10(2))-1;
     h=new int[m];
     if (h==NULL){
           printf(" ERROR ");
           system("Pause");
     }
     h[0]=1;
     for (i=1; i<m; i++) h[i]=2*h[i-1]+1; //����� �����
     for (l=m-1; l>=0; l--) {
         k=h[l];
         for (i=k+1; i<n; i++) {
             t=A[i]; //��� ���������
             for (j=i-k; (j>=0)&&(t<A[j]); j=j-k) A[j+k]=A[j]; //��� ��������� � ���������
             A[j+k]=t; //��� ���������
         }
     }
     delete h;
     h=NULL;
}

void ShellSortMC(int* A, int n)
{
     int i,j,t,k,m,l,*h,M=0,C=0;
     //���������� ������� �����
     m=(int)(log10(n)/log10(2))-1;
     h=new int[m];
     if (h==NULL){
           printf(" ERROR ");
           system("Pause");
     }
     h[0]=1;
     for (i=1; i<m; i++) h[i]=2*h[i-1]+1;
     //���������� ������� �����
     printf("\nK-sort number: %d\nMax step: %d",m,h[m-1]);
//     for (i=1; i<n; i++) {
//         t=A[i]; //��� ���������
//         for (j=i-1; (j>=0)&&(t<A[j]); j--) A[j+1]=A[j]; //��� ��������� � ���������
//         A[j+1]=t; //��� ���������
//     }
     for (l=m-1; l>=0; l--) {
         k=h[l];
         for (i=k; i<n; i++) {
             t=A[i]; M++; //��� ���������
             C++;
             for (j=i-k; (j>=0)&&(t<A[j]); j=j-k) { A[j+k]=A[j]; C++; M++; } //��� ��������� � ���������
             A[j+k]=t; M++;  //��� ���������
         }
     }
     delete h;
     h=NULL;
     printf("\nPractical M and C:\nM=%d C=%d",M,C);
}

main() {
       int *A, n, i, m, c;
       printf("Razmer massiva: ");
       scanf("%d",&n);
       A=new int [n];
       if (A==NULL){
           printf(" ERROR ");
           return 1;
       }
       //c=(n*n-n)/4+(n-1)/2; m=(n*n-n)/4+2*n-2; //��� �������
       //c=n-1; m=2*(n-1); //��� �����������
       //c=(n*n-n)/2; m=(n*n-n)/2+2*n-2; //��� ��������
       //printf("\nTheoretical M and C:\nM=%d C=%d\n",m,c); //��� "��������"
       FillRand(A, n);
       //FillInc(A, n);
       //FillDec(A, n);
       Output(A, n); //����� ��������� �������
       printf("\nSorted:");
       //InsertSortMC(A, n);
       ShellSortMC(A, n);
       Output(A, n); //����� ���������������� �������
       delete A;
       A=NULL;
       system("Pause");
       return 0;
}

