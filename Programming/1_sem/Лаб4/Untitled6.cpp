#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
 short s,x,i,n;
 printf("Vvedite N\n");
 scanf("%d", &n);
 for (s=0, x=0, i=0; i<=n; i++) {
     x=pow(-1,i);
     s=s-i*x;
 }
 printf("S=%d", s);
 getch();  
}
     
