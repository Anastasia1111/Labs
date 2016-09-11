#include <stdio.h>
#include <conio.h>

main (){
 float a,b,c,max,min;
 puts ("Vvedite chisla \n");
 scanf ("%f",&a);
 max=a; min=a;
 scanf ("%f",&b);
 if (b<min) min=b;
 if (b>max) max=b;
 scanf ("%f",&c);
 if (c<min) min=c;
 if (c>max) max=c;
 if (a==max) a=min;
 else if (a==min) a=max;
 if (b==max) b=min;
 else if (b==min) b=max;
 if (c==min) c=max;
 else if (c==max) c=min;

 printf ("Chisla : %f,%f,%f",a,b,c);

 getch();  
}
     
