#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <ctime>
const int N=640; // ширина
const int M=360; // высота

void Fig (int x, int y, int color) { 
     setcolor(color);
     moveto(x-9,y-9);
     lineto(x+9,y+9);
     moveto(x+9,y-9);
     lineto(x-9,y+9);
}

void Lab(int color) {
     int A[M][N],i;
     setcolor(color);
     // Ќачало формиовани€ лабиринта
     for (i=0; i<=60; i++) putpixel(i,0,color); 
     for (i=81; i<=260; i++) putpixel(i,0,color); 
     for (i=0; i<=160; i++) putpixel(260,i,color);
     for (i=181; i<=200; i++) putpixel(260,i,color);
     for (i=0; i<=260; i++) putpixel(i,200,color);
     for (i=0; i<=200; i++) putpixel(0,i,color);
     for (i=61; i<=80; i++) putpixel(i,20,color);
     for (i=141; i<=240; i++) putpixel(i,20,color);
     for (i=61; i<=100; i++) putpixel(i,40,color);
     for (i=181; i<=220; i++) putpixel(i,40,color);
     for (i=1; i<=40; i++) putpixel(i,60,color);
     for (i=81; i<=120; i++) putpixel(i,60,color);
     for (i=21; i<=120; i++) putpixel(i,80,color);
     for (i=201; i<=240; i++) putpixel(i,80,color);
     for (i=41; i<=80; i++) putpixel(i,100,color);
     for (i=181; i<=200; i++) putpixel(i,100,color);
     for (i=61; i<=80; i++) putpixel(i,120,color);
     for (i=121; i<=160; i++) putpixel(i,120,color);
     for (i=201; i<=220; i++) putpixel(i,120,color);
     for (i=21; i<=40; i++) putpixel(i,140,color);
     for (i=101; i<=120; i++) putpixel(i,140,color);
     for (i=141; i<=180; i++) putpixel(i,140,color);
     for (i=201; i<=240; i++) putpixel(i,140,color);
     for (i=61; i<=140; i++) putpixel(i,160,color);
     for (i=181; i<=200; i++) putpixel(i,160,color);
     for (i=221; i<=240; i++) putpixel(i,160,color);
     for (i=121; i<=160; i++) putpixel(i,180,color); 
     for (i=201; i<=240; i++) putpixel(i,180,color);
     for (i=21; i<=60; i++) putpixel(20,i,color);
     for (i=81; i<=180; i++) putpixel(20,i,color);
     for (i=1; i<=40; i++) putpixel(40,i,color);
     for (i=101; i<=120; i++) putpixel(40,i,color);
     for (i=141; i<=180; i++) putpixel(40,i,color);
     for (i=21; i<=80; i++) putpixel(60,i,color);
     for (i=121; i<=160; i++) putpixel(60,i,color);
     for (i=181; i<=200; i++) putpixel(60,i,color);
     for (i=1; i<=20; i++) putpixel(80,i,color);
     for (i=81; i<=100; i++) putpixel(80,i,color);
     for (i=141; i<=180; i++) putpixel(80,i,color);
     for (i=21; i<=40; i++) putpixel(100,i,color);
     for (i=101; i<=140; i++) putpixel(100,i,color);
     for (i=181; i<=200; i++) putpixel(100,i,color); 
     for (i=1; i<=60; i++) putpixel(120,i,color);
     for (i=81; i<=140; i++) putpixel(120,i,color);
     for (i=161; i<=180; i++) putpixel(120,i,color);
     for (i=21; i<=100; i++) putpixel(140,i,color);
     for (i=141; i<=160; i++) putpixel(140,i,color);
     for (i=41; i<=120; i++) putpixel(160,i,color);
     for (i=161; i<=180; i++) putpixel(160,i,color); 
     for (i=21; i<=80; i++) putpixel(180,i,color);
     for (i=101; i<=200; i++) putpixel(180,i,color);
     for (i=61; i<=100; i++) putpixel(200,i,color);
     for (i=121; i<=140; i++) putpixel(200,i,color);
     for (i=161; i<=180; i++) putpixel(200,i,color);
     for (i=41; i<=60; i++) putpixel(220,i,color);
     for (i=101; i<=120; i++) putpixel(220,i,color);
     for (i=141; i<=160; i++) putpixel(220,i,color);
     for (i=21; i<=140; i++) putpixel(240,i,color); 
     //  онец формировани€ лабиринта   
}

void Control() {
   int x,y,ch;
   initwindow (N,M);
   Lab(15);
   x=70; y=10;
   Fig (x,y,15);
   while(1) {
       ch=getch();     
           if (ch==27)
               break; 
           if (ch==97 && getpixel(x-10,y)==0) {Fig (x,y,0); x-=20;}
           if (ch==100 && getpixel(x+10,y)==0) {Fig (x,y,0); x+=20;}
           if (ch==119 && getpixel(x,y-10)==0) {Fig (x,y,0); y-=20;}
           if (ch==115 && getpixel(x,y+10)==0) {Fig (x,y,0); y+=20;}
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

