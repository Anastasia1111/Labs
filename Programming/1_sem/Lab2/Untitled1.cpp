#include <stdio.h>
#include <conio.h>

main (){
float a,b,c,d,e,f,S,P,R;
puts ("Vvedite chisla \n");
scanf ("%f",&a);
scanf ("%f",&b);
scanf ("%f",&c);
scanf ("%f",&d);
scanf ("%f",&e);
scanf ("%f",&f);
S=a+b+c+d+e+f;
P=a*b*c*d*e*f;
if (S>P) {
    R=S-P;     
printf ("Summa bol'she proizvedeniya na %f",R);
}
else { R=P-S;
printf ("Proizvedenie bol'she summi na %f",R); }
getch();  }
     
