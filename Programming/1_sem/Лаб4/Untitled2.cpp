#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
 double s,x;
 short i;
 for (s=0, i=0; i<=25; i++) {
     x=i;
     s=s+sin(x);
 }
 printf("S=%4.3f", s);
 getch();  
}
     
