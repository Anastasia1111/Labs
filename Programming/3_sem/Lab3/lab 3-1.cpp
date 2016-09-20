#include <cstdlib>
#include <graphics.h>
#include <ctime>

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


int main (void) {
	
	srand(time(NULL));
	
	int xBorder = 160;
	int yBorder = 120;
	int i;
	tPoint* arr[100];
	
	
	for ( i = 0; i < 100; i++) 
	{
		arr[i] = new tPoint( xBorder, yBorder );
	}
	
	initwindow( xBorder, yBorder );
	for ( i = 0; i < 100; i++) 
	{
		arr[i]->setPoint();
	}
	
	for ( i = 0; i < 1; i++ )
	{
		arr[i]->LineMoving( xBorder, yBorder );
		while (kbhit())
		{
			getch();
		}
	}
	
	for ( i = 0; i < 1; i++ )
		{
			arr[i]->RandMoving( xBorder, yBorder );
			while (kbhit())
			{
				getch();
			}
		}
	closegraph();
	
}
