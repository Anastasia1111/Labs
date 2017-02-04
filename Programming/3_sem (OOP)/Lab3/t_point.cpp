#include "t_point.h"

tPoint::tPoint()
{
	x = y = color = 0;
}
		
tPoint::~tPoint() 
{
}

void tPoint::setPoint()
{
	y = rand()%ScreenHeight + 1;
	x = rand()%ScreenWidth + 1;
	color = rand()%15+1;	
}

void tPoint::Draw()
{
     putpixel(x,y, color);
}

void tPoint::DirectMoving(int rBorder, int bBorder)
{
        int logX = 1, logY = 1;
    	while (!kbhit()) {
                delay(25);
        		putpixel(x, y, 0);
        		x += logX;
        		y += logY;
        		putpixel(x, y, color);
        		if (x >= rBorder || x <= 0) logX *= (-1);
        		if (y >= bBorder || y <= 0) logY *= (-1);
    		
    	}
    	getch();
}

void tPoint::RandMoving(int rBorder, int bBorder)
{
        int logX = rand()%7 - 3, logY = rand()%7 - 3;
    	while (!kbhit()) {
                delay(25);
        		putpixel(x, y, 0);
        		x += logX;
        		y += logY;
        		putpixel(x, y, color);
        		if (x >= rBorder || x <= 0) logX = rand()%7 - 3;
        		if (y >= bBorder || y <= 0) logY = rand()%7 - 3;
    	}
    	getch();
}
