#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d,e,f,R;
puts ("Vvedite chisla \n");
scanf ("%f",&a);
e=a; f=a;
scanf ("%f",&b);
if (b<f)f=b;
if (b>e)e=b;
scanf ("%f",&c);
if (c<f)f=c;
if (c>e)e=c;
scanf ("%f",&d);
if (d<f)f=d;
if (d>e)e=d;
R=e-f;
printf ("Raznost' = %f",R);

getch();  }
     
