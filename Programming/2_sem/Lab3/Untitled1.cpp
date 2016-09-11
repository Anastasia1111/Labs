#include <cstdio>
#include <cstdlib>
#include <ctime>
main(){
   int *b, *c, *d; 
   int i,n,m=0,k=0;
   srand (time(0));
   printf("Razmer massiva: ");
   scanf("%d",&n);
   b=(int *) malloc(n*sizeof(int));
   if (b==NULL){
       printf(" ERROR ");
       return 1;
   }
   for (i=0;i<n;i++){
       b[i]=rand()%101-50;
       if (b[i]>=0) m++;
       else k++;
   }
   c=(int *) malloc(m*sizeof(int));
   d=(int *) malloc(k*sizeof(int));
   if (b==NULL || c==NULL){
       printf(" ERROR ");
       return 1;
   }
   for (m=k=i=0;i<n;i++){
       if (b[i]>=0) c[m++]=b[i];
       else d[k++]=b[i];
   }
   printf("Ishodny massiv: ");
   for (i=0;i<n;i++) printf("%d ",b[i]);
   printf("\nPolozhitelnie chisla: ");
   for (i=0;i<m;i++) printf("%d ",c[i]);
   printf("\nOtricatelnie chisla: ");
   for (i=0;i<k;i++) printf("%d ",d[i]);
   printf("\n");
   free(b); free(c); free(d);
   b=NULL; c=NULL; d=NULL;
   system("Pause");
   return 0;
}
