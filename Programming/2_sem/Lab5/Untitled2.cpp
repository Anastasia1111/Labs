#include <cstdio>
#include <cstdlib>
const int N=10;
typedef int *pint;

main(){
   int i,j;
   pint *B;
   B=new pint[N];
   for (i=0; i<N; i++) B[i]= new int[i];
   for (i=0; i<N; i++) {
       for (j=0; j<i; j++) { 
           B[i][j]=i*(j+1); // ���� ��������� i � j �� 1, � ��������� ��������, ��� i*j �� ���������� �����.
           printf("%3d",B[i][j]); 
       }
       printf("\n");
   }
   for (i=0; i<N; i++)  delete B[i];
   delete B;
   B=NULL;
   system("Pause");
   return 0;
}
