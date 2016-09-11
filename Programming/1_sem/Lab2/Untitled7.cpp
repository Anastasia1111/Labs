#include <stdio.h>
#include <conio.h>

main (){
float k,m,n,e,f,s;
puts ("Vvedite chisla \n");
scanf ("%f",&k);
scanf ("%f",&m);
scanf ("%f",&n);
if(k>m) {e=k; k=m;m=e;}
if(k>n) {e=k; k=n;n=e;}
if(m>n) {e=m; m=n; n=e;}
printf ("K=%f, M=%f, N=%f",k,m,n);

getch();  }
     
