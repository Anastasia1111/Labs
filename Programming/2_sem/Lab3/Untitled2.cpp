#include <cstdio>
#include <cstdlib>
#include <ctime>
main(){
   float *a, **b, *t; 
   int i,j,n,min;
   srand (time(0));
   printf("Razmer massiva: ");
   scanf("%d",&n);
   a=new float [n]; b=new float* [n];
   if (a==NULL || b==NULL){
       printf(" ERROR ");
       return 1;
   }
   for (i=0;i<n;i++){
       a[i]=(float)rand()*(25-n)/RAND_MAX + n;
       b[i]=&a[i];
   }
   printf("Ishodny massiv:\n");
   for (i=0;i<n;i++) printf("%4.2f ",a[i]);
   for (i=0; i<n-1; i++) {
       min=i;
       for (j=i+1; j<n; j++)
           if (*b[min]>*b[j]) min=j;
       t=b[i]; b[i]=b[min]; b[min]=t;
   }
   printf("\nOtsortirovanniy massiv: \n");
   for (i=0;i<n;i++) printf("%4.2f ",*b[i]);
   printf("\n");
   delete a; delete b;
   a=NULL; b=NULL;
   system("Pause");
   return 0;
}
