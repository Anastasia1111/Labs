#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
 double s,x;
 short i,n;
 printf("Vvedite N\n");
 scanf("%d", &n);
 for (s=0, i=0; i<=n; i++) {
     x=i*2;
     s=s+tan(x);
 }
 printf("S=%f", s);
 getch();  
}
     
