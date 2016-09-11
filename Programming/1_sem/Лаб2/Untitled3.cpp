#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d;
puts ("Vvedite chisla \n");
scanf ("%f",&a);
scanf ("%f",&b);
scanf ("%f",&c);
scanf ("%f",&d);
if (a<0) a=0;
if (b<0) b=0;
if (c<0) c=0;
if (d<0) d=0;
printf ("a=%f,b=%f,c=%f,d=%f",a,b,c,d);

getch();  }
     
