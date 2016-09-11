//  ВАРИАНТ 14  |  СВОБОДНОЕ ДВИЖЕНИЕ 4  |  ГРАФИЧЕСКИЙ ОБЪЕКТ 6  |  ДВИЖЕНИЕ 2  |
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <ctime>
const int N=640; // ширина
const int M=360; // высота
//Программа расчитана на соотношение сторон 16:9

void Fig (int x, int y, int color) { 
     setcolor(color);
     moveto(x-55,y-35);
     lineto(x-45,y-35);
     lineto(x-40,y-25);
     lineto(x-30,y-25);
     lineto(x-15,y-30);
     lineto(x-10,y-25);
     lineto(x,y-25);
     circle(x,y-20,5);
     setfillstyle(1,0);
     bar(x-6,y-24,x,y-16);
     moveto(x,y-15);
     lineto(x-45,y-15);
     lineto(x-55,y-35);
     moveto(x-35,y-20);
     lineto(x-45,y);
     lineto(x-40,y);
     lineto(x-15,y-20);
}

void Draw () {
   int x,y,i=0,k=1;
   initwindow (N,M);
   x=55; y=35;
   while(1) {
       if (i%4==0) 
           for(y; y<M; y+=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x+=16;
           }
       if (i%4==1) {
           for(y; y-35>=M/2; y-=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x-=16;
           }
           for(y; y-35>0; y-=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x+=16;
           }
       }
       if (i%4==2)
           for(y; y<M; y+=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x-=16;
           }
       if (i%4==3) {
           for(y; y-35>=M/2; y-=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x+=16;
           }
           for(y; y-35>0; y-=9) {
               if (kbhit())
                     if (getch()==27)
                        break;
                 Fig (x,y,15);
                 delay (200); 
                 Fig (x,y,0);
                 x-=16;
           }
       }
       i++;
   }
   closegraph();
}

void Control() {
   int x,y;
   initwindow (N,M);
   x=55; y=35;
   Fig (x,y,15);
   while(1) {
       if (kbhit()) {
           if (getch()==27)
               break; 
           if (getch()==97) {Fig (x,y,0); x-=16;}
           if (getch()==100) {Fig (x,y,0); x+=16;}
           if (getch()==119) {Fig (x,y,0); y-=9;}
           if (getch()==115) {Fig (x,y,0); y+=9;}
       }
       Fig (x,y,15);
   }
}

main() {
       int c;
       printf(" Menu:\n 1.Free Run\n 2.Control Run\n 3.Exit\n");
       scanf("%d",&c);
       switch(c) {
                 case 1: Draw(); break;
                 case 2: Control(); break;
                 case 3: getch(); break;
       }
}

