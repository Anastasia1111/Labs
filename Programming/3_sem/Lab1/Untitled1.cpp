#include <cstdio>
#include <cstdlib>

const int N=5;

main(){
   int i,j;
   int* *E;
   E=new int*[N];
   for (i=0; i<N; i++) E[i]= new int[N];
   for (i=0; i<N; i++) {
       for (j=0; j<N; j++) { 
           E[i][j]=rand()%50;
           printf("%3d",E[i][j]); 
       }
       printf("\n");
   }
   printf("\n***********ISH***********\n");
   int *A = new int [N*N];
   int a = 0;
   for (i=0; i<N; i++) {
       for (j=N-i; j<N; j++, a++) { 
           A[a] = E[i][j];
           printf("%3d",A[a]); 
       }
   }
   printf("\n***********A***********\n");
   int *B = new int [N*N];
   int b = 0;
   for (i=0; i<N; i++) {
       for (j=i; j>=0; j--, b++) { 
           B[b] = E[i][j];
           printf("%3d",B[b]); 
       }
   }
   printf("\n************B**********\n");
   int *C = new int [N*N];
   int c = 0; 
   i = j = (N-1)/2;
   int logI=-1, logJ=-1, q;
   for (int step=1; step<N; step++){
       logI = logI*(-1); 
       logJ = logJ*(-1);
       for(q = 0; q < step; q++, c++){
             C[c]=E[i][j];
             i += logI;
             printf("%3d",C[c]); 
       }
       for(q = 0; q < step; q++, c++){
             C[c]=E[i][j];
             j += logJ;
             printf("%3d",C[c]); 
       }
   }
   printf("\n***********C***********\n");
   int *D = new int [N*N];
   int d = 0; 
   i = j = 0;
   logI=-1; logJ=-1;
   for (int step=N-1; step>=0; step--){
       logI = logI*(-1); 
       logJ = logJ*(-1);
       for(q = 0; q < step; q++, d++){
             D[d]=E[i][j];
             i += logI;
             printf("%3d",D[d]); 
       }
       for(q = 0; q < step; q++, d++){
             D[d]=E[i][j];
             j += logJ;
             printf("%3d",D[d]); 
       }
   }
   printf("\n***********D***********\n");
   int* *G;
   int g1 = rand()%10+1;
   int g2 = rand()%10+1;
   G=new int*[g1];
   for (i=0; i<g1; i++) G[i]= new int[g2];
   /*for (i=0; i<g1; i++) {
       for (j=0; j<i; j++) { 
           B[i][j]=i*(j+1);
           printf("%3d",B[i][j]); 
       }
       printf("\n");
   }*/
   system("Pause");
   return 0;
}
