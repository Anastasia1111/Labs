#include "geometry.h"

Geometry::Geometry()
{
	x = y = color = 0;
}

void Geometry::set(int _x, int _y, int _color)
{
	y = _y;
	x = _x;
	color = _color;	
}

void Geometry::DirectMoving(int rBorder, int bBorder)
{
        int logX = 1, logY = 1;
    	while (!kbhit()) {
                delay(25);
        		Draw(0);
        		x += logX;
        		y += logY;
        		Draw(color);
        		if (x >= rBorder || x <= 0) logX *= (-1);
        		if (y >= bBorder || y <= 0) logY *= (-1);
    		
    	}
    	getch();
}

void Geometry::RandMoving(int rBorder, int bBorder)
{
        int logX = rand()%7 - 3, logY = rand()%7 - 3;
    	while (!kbhit()) {
                delay(25);
        		Draw(0);
        		x += logX;
        		y += logY;
        		Draw(color);
        		if (x >= rBorder || x <= 0) logX = rand()%7 - 3;
        		if (y >= bBorder || y <= 0) logY = rand()%7 - 3;
    	}
    	getch();
}
