#include "classfile.h"

class tPoint 
{
	private:
		int x;
		int y;
		int color;
		
	public:
		tPoint()
		{
			x = y = color = 0;
		}
		
		setPoint()
		{
			y = rand()%480 + 1;
			x = rand()%640 + 1;
			color = rand()%16;	
		}
		
		LineMoving(int rBorder, int bBorder)
		{
			int logX = 1, logY = 1;
			while (!kbhit()) {
				putpixel(x, y, 0);
				putpixel(x, y, color);
				x += logX;
				y += logY;
				if (x >= rBorder || x <= 0) logX *= (-1);
				if (y >= bBorder || y <= 0) logY *= (-1);
				
			}
		}
		
		RandMoving(int rBorder, int bBorder)
		{
			int logX = rand()%7 - 3, logY = rand()%7 - 3;
			while (!kbhit()) {
				putpixel(x, y, 0);
				putpixel(x, y, color);
				x += logX;
				y += logY;
				if (x >= rBorder || x <= 0) logX = rand()%7 - 3;
				if (y >= bBorder || y <= 0) logY = rand()%7 - 3;
			}
		}
		
		~tPoint() {}

};
