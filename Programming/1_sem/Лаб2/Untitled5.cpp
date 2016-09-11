#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d,e,f;
puts ("Vvedite chisla \n");
e=1;
scanf ("%f",&a);
f=a;
scanf ("%f",&b);
if (b<f){ e=2; f=b;}
scanf ("%f",&c);
if (c<f){ e=3; f=c;}
scanf ("%f",&d);
if (d<f){ e=4; f=d;}
printf ("Naimen'shee chislo - nomer %f",e);

getch();  }
     
