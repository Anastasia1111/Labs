#include <stdio.h>
#include <conio.h>

main (){
 int n,i;
 double x,p,q;
 printf("Vvedite N\n");
 scanf("%d", &n);
 q=1;
 for (x=5, q=1., p=1, i=1; i<=n; x*=5,i++)
 {
     p=p*i;
     q=q+(x/p);  	
 }
 printf("P=%5.2f", q);
 getch();  
}
        
