#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d,e,f,g,h,P,O;
P=0;
O=0;
puts ("Vvedite chisla \n");
scanf ("%f",&a);
scanf ("%f",&b);
scanf ("%f",&c);
scanf ("%f",&d);
scanf ("%f",&e);
scanf ("%f",&f);
scanf ("%f",&g);
scanf ("%f",&h);
a>0 ? P=P+1 : O=O+1;
b>0 ? P=P+1 : O=O+1;
c>0 ? P=P+1 : O=O+1;
d>0 ? P=P+1 : O=O+1;
e>0 ? P=P+1 : O=O+1;
f>0 ? P=P+1 : O=O+1;
g>0 ? P=P+1 : O=O+1;
h>0 ? P=P+1 : O=O+1;
printf ("Polojitel'nih :%f, Otricatel'nih :%f",P,O);

getch();  }
     
