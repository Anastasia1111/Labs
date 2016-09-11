#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
 double s,y,x;
 short i;
 for (s=0., x=1., i=1; i<=10; i++) {
     y=(0.16+0.02*i)*x;
     s=s+pow(y,i);   
 }
 printf("S=%4.3f", s);
 getch();  
}
