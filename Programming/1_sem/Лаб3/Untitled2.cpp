#include <stdio.h>
#include <conio.h>

main (){
 int c;
 printf("Vvedite chislo: \n");
 scanf("%d", &c);
 switch(c)
 {
          case -9:
               printf("Minus devyat' \n"); break;
          case -8:
               printf("Minus vosem' \n"); break;
          case -7:
               printf("Minus sem' \n"); break;
          case -6:
               printf("Minus shest' \n"); break;
          case -5:
               printf("Minus pyat' \n"); break;
          case -4:
               printf("Minus chetire \n"); break;
          case -3:
               printf("Minus tri \n"); break;
          case -2:
               printf("Minus dva \n"); break;
          case -1:
               printf("Minus odin \n"); break;
          case 9:
               printf("devyat' \n"); break;
          case 8:
               printf("vosem' \n"); break;
          case 7:
               printf("sem' \n"); break;
          case 6:
               printf("shest' \n"); break;
          case 5:
               printf("pyat' \n"); break;
          case 4:
               printf("chetire \n"); break;
          case 3:
               printf("tri \n"); break;
          case 2:
               printf("dva \n"); break;
          case 1:
               printf("odin \n"); break;
          case 0:
               printf ("nol' \n"); break;                                                                                                     
          default: printf("\n Error. Vvedite drugoe chislo posle perezapuska \n");
 }          
 getch();  
}
     
