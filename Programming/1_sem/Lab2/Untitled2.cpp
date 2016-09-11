#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d,e,S;
S=0;
puts ("Vvedite chisla \n");
scanf ("%f",&a);
scanf ("%f",&b);
scanf ("%f",&c);
scanf ("%f",&d);
scanf ("%f",&e);
if (a>0) S=S+a;
if (b>0) S=S+b;
if (c>0) S=S+c;
if (d>0) S=S+d;
if (e>0) S=S+e;
printf ("Summa =%f",S);

getch();  }
     
