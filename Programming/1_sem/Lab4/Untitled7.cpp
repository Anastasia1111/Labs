#include <stdio.h>
#include <conio.h>

main (){
 short p,m,i;
 printf("Vvedite M\n");
 scanf("%d", &m);
 for (p=1, i=1; i<=m; i++)
     p=p*i;
 printf("P=%d", p);
 getch();  
}
     
