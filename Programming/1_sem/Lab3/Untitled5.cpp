#include <stdio.h>
#include <conio.h>

main (){
 int m,d,t;
 printf("Vvedite den' i mesyac: \n");
 scanf("%d, %d", &d, &m);
 switch(m)
 {
          case 1:
               t=0; break;
          case 2:
               t=31; break;
          case 3:
               t=59; break;
          case 4:
               t=90; break;
          case 5:
               t=120; break;
          case 6:
               t=151; break;
          case 7:
               t=181; break;
          case 8:
               t=211; break;
          case 9:
               t=242; break;
          case 10:
               t=273; break;
          case 11:
               t=303; break;
          case 12:
               t=334; break;                                                                                           
          default: printf("\n Error. Vvedite drugoi mesyac posle perezapuska \n");
 } 
 t=t+d;
 printf(" T=%d", t);    
 getch();  
}
     
