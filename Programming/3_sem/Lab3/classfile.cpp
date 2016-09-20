#include "classfile.h"

class tPoint 
{
	private:
		int x;
		int y;
		int color;
		
	public:
		// constructor
		tPoint( int rBorder, int bBorder )
		{
			y = rand()%bBorder + 1;
			x = rand()%rBorder + 1;
			color = rand()%16 + 1;	
		}
		
		tPoint () 
		{
			x = y = color = 0;
		}
		
		// methods
		
		void setPoint ()
		{
			putpixel( x, y, color );
		}
		
		void LineMoving(int rBorder, int bBorder)
		{
			int logX = 1, logY = 1, i = 0;
			while (i < 300) {
				putpixel(x, y, 0);
				x += logX;
				y += logY;
				if (x > rBorder || x < 0) logX *= (-1);
				if (y > bBorder || y < 0) logY *= (-1);
				putpixel(x, y, color);
				delay(50);	
				i++;
			}
		}
		
		void RandMoving(int rBorder, int bBorder)
		{
			int logX = rand()%7 - 3, logY = rand()%7 - 3, i = 0;
			while (i < 300) {
				putpixel(x, y, 0);
				x += logX;
				y += logY;
				if (x > rBorder || x < 0) logX = rand()%7 - 3;
				if (y > bBorder || y < 0) logY = rand()%7 - 3;
				putpixel(x, y, color);
				delay(50);
				i++;
			}
		}
		
		~tPoint() {}

};
