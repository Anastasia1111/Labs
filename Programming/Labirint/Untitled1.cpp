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

void Menu() {
     int c=1, M1[6300], M2[6300], *p, ch;
     initwindow (90,70);
       outtextxy(0,0,"Menu:");
       outtextxy(0,20,"1.Control Run");
       outtextxy(0,40,"2.Exit");
       getimage(0,20,textwidth("1.Control Run")-1,20+textheight("1.Control Run")-1,M1);
       getimage(0,40,textwidth("2.Exit")-1,40+textheight("2.Exit")-1,M2);
       p=M1;   
       while (1) {
           putimage(0,20*c,p,0);
           delay(500);
           if (kbhit()) {
               ch=getch();
               if (ch==119) c--;
               if (ch==115) c++;
               if (ch==13) {
                   if (c==1) {closegraph(); Control();}
                   if (c==2) {closegraph();}
               }
           }
           if (c==0) c=2;
           if (c==3) c=1;
           if (c==1) p=M1;
           if (c==2) p=M2;
           putimage(0,20*c,p,4);
           delay(500);
   }
}

main() {
       Menu();
       getch();
}

