#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <ctime>
const int N=300; // ширина
const int M=300; // высота
const int R=50; // размер клетки

void Fig (int x, int y, int color) { 
     setcolor(color);
     moveto(x-(R/2-1),y-(R/2-1));
     lineto(x+(R/2-1),y+(R/2-1));
     moveto(x+(R/2-1),y-(R/2-1));
     lineto(x-(R/2-1),y+(R/2-1));
}

void Lab(int x, int y, int color) { // x,y - начало координат
     int i;
     setcolor(color);
     // Начало формиования лабиринта
     for (i=0; i<=3*R; i++) putpixel(x+i,y+0,color); 
     for (i=4*R+1; i<=13*R; i++) putpixel(x+i,y+0,color); 
     for (i=0; i<=8*R; i++) putpixel(x+13*R,y+i,color);
     for (i=9*R+1; i<=10*R; i++) putpixel(x+13*R,y+i,color);
     for (i=0; i<=13*R; i++) putpixel(x+i,y+10*R,color);
     for (i=0; i<=10*R; i++) putpixel(x+0,y+i,color);
     for (i=3*R+1; i<=4*R; i++) putpixel(x+i,y+R,color);
     for (i=7*R+1; i<=12*R; i++) putpixel(x+i,y+R,color);
     for (i=3*R+1; i<=5*R; i++) putpixel(x+i,y+2*R,color);
     for (i=9*R+1; i<=11*R; i++) putpixel(x+i,y+2*R,color);
     for (i=1; i<=2*R; i++) putpixel(x+i,y+3*R,color);
     for (i=4*R+1; i<=6*R; i++) putpixel(x+i,y+3*R,color);
     for (i=R+1; i<=6*R; i++) putpixel(x+i,y+4*R,color);
     for (i=10*R+1; i<=12*R; i++) putpixel(x+i,y+4*R,color);
     for (i=2*R+1; i<=4*R; i++) putpixel(x+i,y+5*R,color);
     for (i=9*R+1; i<=10*R; i++) putpixel(x+i,y+5*R,color);
     for (i=3*R+1; i<=4*R; i++) putpixel(x+i,y+6*R,color);
     for (i=6*R+1; i<=8*R; i++) putpixel(x+i,y+6*R,color);
     for (i=10*R+1; i<=11*R; i++) putpixel(x+i,y+6*R,color);
     for (i=R+1; i<=2*R; i++) putpixel(x+i,y+7*R,color);
     for (i=5*R+1; i<=6*R; i++) putpixel(x+i,y+7*R,color);
     for (i=7*R+1; i<=9*R; i++) putpixel(x+i,y+7*R,color);
     for (i=10*R+1; i<=12*R; i++) putpixel(x+i,y+7*R,color);
     for (i=3*R+1; i<=7*R; i++) putpixel(x+i,y+8*R,color);
     for (i=9*R+1; i<=10*R; i++) putpixel(x+i,y+8*R,color);
     for (i=11*R+1; i<=12*R; i++) putpixel(x+i,y+8*R,color);
     for (i=6*R+1; i<=8*R; i++) putpixel(x+i,y+9*R,color); 
     for (i=10*R+1; i<=12*R; i++) putpixel(x+i,y+9*R,color);
     for (i=R+1; i<=3*R; i++) putpixel(x+R,y+i,color);
     for (i=4*R+1; i<=9*R; i++) putpixel(x+R,y+i,color);
     for (i=1; i<=2*R; i++) putpixel(x+2*R,y+i,color);
     for (i=5*R+1; i<=6*R; i++) putpixel(x+2*R,y+i,color);
     for (i=7*R+1; i<=9*R; i++) putpixel(x+2*R,y+i,color);
     for (i=R+1; i<=4*R; i++) putpixel(x+3*R,y+i,color);
     for (i=6*R+1; i<=8*R; i++) putpixel(x+3*R,y+i,color);
     for (i=9*R+1; i<=10*R; i++) putpixel(x+3*R,y+i,color);
     for (i=1; i<=R; i++) putpixel(x+4*R,y+i,color);
     for (i=4*R+1; i<=5*R; i++) putpixel(x+4*R,y+i,color);
     for (i=7*R+1; i<=9*R; i++) putpixel(x+4*R,y+i,color);
     for (i=R+1; i<=2*R; i++) putpixel(x+5*R,y+i,color);
     for (i=5*R+1; i<=7*R; i++) putpixel(x+5*R,y+i,color);
     for (i=9*R+1; i<=10*R; i++) putpixel(x+5*R,y+i,color); 
     for (i=1; i<=3*R; i++) putpixel(x+6*R,y+i,color);
     for (i=4*R+1; i<=7*R; i++) putpixel(x+6*R,y+i,color);
     for (i=8*R+1; i<=9*R; i++) putpixel(x+6*R,y+i,color);
     for (i=R+1; i<=5*R; i++) putpixel(x+7*R,y+i,color);
     for (i=7*R+1; i<=8*R; i++) putpixel(x+7*R,y+i,color);
     for (i=2*R+1; i<=6*R; i++) putpixel(x+8*R,y+i,color);
     for (i=8*R+1; i<=9*R; i++) putpixel(x+8*R,y+i,color); 
     for (i=R+1; i<=4*R; i++) putpixel(x+9*R,y+i,color);
     for (i=5*R+1; i<=10*R; i++) putpixel(x+9*R,y+i,color);
     for (i=3*R+1; i<=5*R; i++) putpixel(x+10*R,y+i,color);
     for (i=6*R+1; i<=7*R; i++) putpixel(x+10*R,y+i,color);
     for (i=8*R+1; i<=9*R; i++) putpixel(x+10*R,y+i,color);
     for (i=2*R+1; i<=3*R; i++) putpixel(x+11*R,y+i,color);
     for (i=5*R+1; i<=6*R; i++) putpixel(x+11*R,y+i,color);
     for (i=7*R+1; i<=8*R; i++) putpixel(x+11*R,y+i,color);
     for (i=R+1; i<=7*R; i++) putpixel(x+12*R,y+i,color); 
     // Конец формирования лабиринта   
}

void Control() {
   int x,y,xi,yi,ch;
   initwindow (N,M);
   x=0; y=M/2;
   Lab(x,y,15);
   xi=4*R-R/2+x; yi=R/2+y;
   Fig (xi,yi,15); // координаты игрока - середина клетки начала лабиринта
   while(1) {
       ch=getch();     
           if (ch==27)
               break; 
           if (ch==97 && getpixel(xi-(R/2),yi)==0) {Lab (x,y,0); x+=R;}
           if (ch==100 && getpixel(xi+(R/2),yi)==0) {Lab (x,y,0); x-=R;}
           if (ch==119 && getpixel(xi,yi-(R/2))==0) {Lab (x,y,0); y+=R;}
           if (ch==115 && getpixel(xi,yi+(R/2))==0) {Lab (x,y,0); y-=R;}
       Lab (x,y,15);
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

