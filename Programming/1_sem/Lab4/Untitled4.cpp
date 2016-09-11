#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
 double i,s;
 for (s=0, i=0.1; i<1.95; i+=0.2) {
     s=s+log(i);
 }
 printf("S=%4.3f", s);
 getch();  
}
     
