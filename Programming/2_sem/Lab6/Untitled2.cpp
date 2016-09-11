#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
const float p=0.45;
const float q=1-p;
//Программа работает для малых m и n из-за слищком больших значений m! и n!
bool Ver(int m, int n, float &pd, float &pm) {
     int nf=1, mf=1, nmf=1, i;
     float cnm;
     if (m<=n) {
         for (i=1; i<=n; i++) nf*=i;
         for (i=1; i<=m; i++) mf*=i;
         for (i=1; i<=(n-m); i++) nmf*=i;
         cnm=(float)nf/(mf*nmf);
         pd=cnm*pow(p,m)*pow(q,n-m); 
         pm=cnm*pow(q,m)*pow(p,n-m);         
         return 1;
     } else return 0;
}

main(){
   int m, n;
   bool elvl;
   float vermal, verdev;
   printf ("m=");
   scanf ("%d",&m);
   printf ("n=");
   scanf ("%d",&n);
   elvl=Ver(m,n,verdev,vermal);
   if (elvl) {
       printf("Dlya devochek: %f \nDlya malchikov: %f \n",verdev,vermal);
   } else printf("ERROR\n");
   system("Pause");
}
