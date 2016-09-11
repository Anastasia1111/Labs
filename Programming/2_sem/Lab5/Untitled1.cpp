#include <cstdio>
#include <cstdlib>
#include <ctime>
typedef int *pint;

main(){
   int i,j,m,k,ks,z;
   pint A, *B;
   srand (time(0));
   printf("m: ");
   scanf("%d",&m);
   printf("k(k<m): ");
   scanf("%d",&k);
   A=new int[m];
   if (A==NULL){
       printf(" ERROR ");
       return 1;
   }
   printf("String: \n");
   for (i=0; i<m; i++){
           A[i]=rand()%21;
           printf("%3d",A[i]);
   }
   ks=m/k; if (m%k) ks++;
   printf("\nMatrix: \n");
   B=new  pint [ks];
   for (i=0; i<ks; i++) B[i]= new int[k];
   for (i=0,z=0; i<ks; i++) {
       for (j=0; j<k; j++) { 
           if (z<m) 
               B[i][j]=A[z]; 
           else  
               B[i][j]=0;
           z++; 
           printf("%3d",B[i][j]); 
       }
       printf("\n");
   }
   for (i=0; i<ks; i++)  delete B[i];
   delete B;
   delete A;
   A=NULL;
   system("Pause");
   return 0;
}
