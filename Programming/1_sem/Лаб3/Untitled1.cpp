#include <stdio.h>
#include <conio.h>

main (){
 short m;
 printf("Vvedite mesyac: \n");
 scanf("%d", &m);
 switch(m)
 {
          case 1:case 2:case 3:case 4:case 5:case 6:
               printf("Pervoe polugodie \n"); break;
          case 7:case 8:case 9:case 10:case 11:case 12:
               printf("Vtoroe polugodie \n"); break;
          default: printf("\n Error \n");
 }  
 switch(m)
 {
          case 1:case 2:case 3:
               printf("Perviy kvartal \n"); break;
          case 4:case 5:case 6:
               printf("Vtoroy kvartal \n"); break;
          case 7:case 8:case 9:
               printf("Tretiy kvartal \n"); break;
          case 10:case 11:case 12:
               printf("Chetvertiy kvartal \n"); break;
          default: printf("\n Error \n");
 }          
 getch();  
}
     
