#include <cstdio>
#include <cstdlib>
#include <ctime>
const int N=5;
typedef int row[N+1];

main(){
   int i,j,m,sum;
   row *A;
   srand (time(0));
   printf("Kolichestvo strok: ");
   scanf("%d",&m);
   A=new row [m+1];
   if (A==NULL){
       printf(" ERROR ");
       return 1;
   }
   printf("Ishodny massiv: \n");
   for (i=0; i<m; i++){
       sum=0;
       for (j=0; j<N; j++) {
           A[i][j]=rand()%21;
           printf("%4d",A[i][j]);
           sum+=A[i][j];
       }
       A[i][N]=sum;
       printf("\n");
   }
   for (j=0; j<=N; j++){
       sum=0;
       for (i=0; i<m; i++) {
           sum+=A[i][j];
       }
       A[N][j]=sum;
   }
   printf("\nRasshirenniy massiv: \n");
   for (i=0; i<=m; i++){
       for (j=0; j<=N; j++) {
           printf("%4d",A[i][j]);
       }
       printf("\n");
   }
   delete A;
   A=NULL;
   system("Pause");
   return 0;
}
