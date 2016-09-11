// Снежинки - точки
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <ctime>
const int N=640; // ширина
const int M=360; // высота
const int R=100;

void Draw ( int x, int y, int color) { 
     setcolor(color);
     moveto(x,y);
     lineto(x+10,y+10);
     moveto(x+10,y);
     lineto(x,y+10);
     moveto(x+5,y);
     lineto(x+5,y+10);
     moveto(x,y+5);
     lineto(x+10,y+5);
}
main() {
   int X[100], Y[100], i;
   srand(time(0));
   for (i=0; i<R; i++) {
       X[i]=rand()%(N-1);
       Y[i]=rand()%(N-1);
   }
   initwindow (N,M);
   i=0; 
   while (1) {
         if ( kbhit() ) // если нажата клавиша…
             if ( getch() == 27 )  // если нажата Esc
                 break; // выход из цикла
         Draw (X[rand()%R],Y[rand()%R],rand()%15-1); Draw (X[rand()%R],Y[rand()%R],0);
         delay (20); // задержка 20 мс
         i++;
         if (i==R) i=0;
   }
   closegraph(); // закрываем графическое окно
   getch();
}

