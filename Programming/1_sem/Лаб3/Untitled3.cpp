#include <stdio.h>
#include <conio.h>

main (){
 int c;
 printf("Vvedite god: \n");
 scanf("%d", &c);
 while (c>12) {c=c-12;}
 switch(c)
 {
          case 1:
               printf("Petuh \n"); break;
          case 2:
               printf("Sobaka \n"); break;
          case 3:
               printf("Svin'ya \n"); break;
          case 4:
               printf("Krisa \n"); break;
          case 5:
               printf("Korova \n"); break;
          case 6:
               printf("Tigr \n"); break;
          case 7:
               printf("Zayac \n"); break;
          case 8:
               printf("Dracon \n"); break;
          case 9:
               printf("Zmeya \n"); break;
          case 10:
               printf("Loshad' \n"); break;
          case 11:
               printf("Ovca \n"); break;
          case 12:
               printf("Obez'yana \n"); break;                                                                                            
          default: printf("\n Error. Vvedite drugoe chislo posle perezapuska \n");
 }          
 getch();  
}
     
