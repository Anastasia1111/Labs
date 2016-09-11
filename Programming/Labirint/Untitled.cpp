#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <ctime>
const int N=640; // ширина
const int M=360; // высота

void Fig (int x, int y, int color) { 
     setcolor(color);
     circle(x,y,10);
     setfillstyle(1,color);
     floodfill(x,y,color);
}

void Control() {
   int x,y;
   initwindow (N,M);
   x=10; y=10;
   Fig (x,y,15);
   while(1) {
       getch();     
           if (getch()==27)
               break; 
           if (getch()==97) {Fig (x,y,0); x-=10;}
           if (getch()==100) {Fig (x,y,0); x+=10;}
           if (getch()==119) {Fig (x,y,0); y-=10;}
           if (getch()==115) {Fig (x,y,0); y+=10;}
       Fig (x,y,15);
   }
}

main() {
       int c;
       printf(" Menu:\n 1.Control Run\n 2.Exit\n");
       scanf("%d",&c);
       switch(c) {
                 case 1: Control(); break;
                 case 2: getch(); break;
       }
}

