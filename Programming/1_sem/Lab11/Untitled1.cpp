// 10 �������
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <graphics.h>
const int N=640; // ������
const int M=360; // ������
const int OX=250;
const int OY=300;
// ������������� ��������� ��� OX � OY: 250 � 50 ��� C=10.
const int C=9;

main (){
     int i,y,a,b;
     a=b=0;
     initwindow(N,M); 
     moveto(0,OY-9*C);       
     lineto(N,OY-9*C);       
     moveto(OX,OY);
     for (i=0; i<=N; i++) {
         y=(i+2)*(i+2);
         if (y==9) a=i;
         if (y<=M) { lineto(i*C+OX,-y+OY); continue;}
         break; 
     }
//     //����������� �������� ���������� "�������" ��������: (-75;31) � (35;30) ��� �=10.
//     putpixel(OX-75,OY-31,15); putpixel(OX+35,OY-30,15); //�������
     moveto(OX,OY);
     for (i=0; i>=-N; i--) {
         y=(i+2)*(i+2);
         if (y==9) b=i;
         if (y<=M) { lineto(i*C+OX,-y+OY); continue;}
         break; 
     }
     setfillstyle(1,1);
     floodfill(OX,OY-8*C,15);
     moveto(0,OY); lineto(N,OY); //��� ��
     moveto(OX,0); lineto(OX,N); //��� OY
     outtextxy (300+OX, OY-9*C-20, "f(x)=9;" );
     outtextxy (OX+8*C+1, OY-99, "f(x)=sqr(x+2);" );
     printf("a=%d b=%d",a,b);
     getch();
}
