#include <stdio.h>
#include <conio.h>

main (){
float k,m,n,e,f;
puts ("Vvedite chisla \n");
scanf ("%f",&k);
scanf ("%f",&m);
scanf ("%f",&n);
scanf ("%f",&f);
if(k>m) {e=k; k=m;m=e;}
if(k>n) {e=k; k=n;n=e;}
if(k>f) {e=k; k=f;f=e;}
if(m>n) {e=m; m=n; n=e;}
if(m>f) {e=m; m=f; f=e;}
if(n>f) {e=n; n=f; f=e;}
printf ("Naibol'shee 1=%f,Naibol'shee 2=%f",n,f);

getch();  }
     
