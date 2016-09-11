#include <cstdio>
#include <cstdlib>
#include <ctime>
const int N=5;
typedef int row[N];
typedef int lrow[N-1];

main(){
   int i,j,m,maxi=0,maxj=0;
   row *B;
   lrow *C;
   srand (time(0));
   printf("Kolichestvo strok: ");
   scanf("%d",&m);
   B=new row [m]; C=new lrow [m-1];
   if (B==NULL || C==NULL){
       printf(" ERROR ");
       return 1;
   }
   printf("Ishodny massiv: \n");
   for (i=0; i<m; i++){
       for (j=0; j<N; j++) {
           B[i][j]=rand()%21;
           printf("%3d",B[i][j]);
           if (B[i][j]>B[maxi][maxj]) { maxi=i; maxj=j; }
       }
       printf("\n");
   }
   printf("\nSokrashenniy massiv: \n");
   for (i=0; i<m-1; i++){
       if (i<maxi) {
           for (j=0; j<N-1; j++) {
               if (j<maxj) {   
                   C[i][j]=B[i][j];
                   printf("%3d",C[i][j]);
               }
               if (j>=maxj) {   
                   C[i][j]=B[i][j+1];
                   printf("%3d",C[i][j]);
               }
           }
           printf("\n");
       }
       if (i>=maxi) {
           for (j=0; j<N-1; j++) {
               if (j<maxj) {   
                   C[i][j]=B[i+1][j];
                   printf("%3d",C[i][j]);
               }
               if (j>=maxj) {   
                   C[i][j]=B[i+1][j+1];
                   printf("%3d",C[i][j]);
               }
           }
           printf("\n");
       }
   }
   delete B; delete C;
   B=NULL; C=NULL;
   system("Pause");
   return 0;
}
