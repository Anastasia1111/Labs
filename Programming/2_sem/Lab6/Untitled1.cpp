#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

bool PerPl(int a, int b, int c, int *P, float *S) {
     float p= (float)(a+b+c)/2;
     if ((a+b)>c && (a+c)>b &&(b+c)>a) {
         *S=sqrt(p*(p-a)*(p-b)*(p-c));
         *P=a+b+c;
         return 1;
     } else return 0;
}

main(){
   int a, b, c, per;
   bool elvl;
   float plosh;
   printf ("a=");
   scanf ("%d",&a);
   printf ("b=");
   scanf ("%d",&b);
   printf ("c=");
   scanf ("%d",&c);
   elvl=PerPl(a,b,c,&per,&plosh);
   if (elvl) {
       printf("P=%d \nS=%4.2f \n",per,plosh);
   } else printf("ERROR");
   system("Pause");
}
