#include <cmath>
#include "rectangle.h"

void Rectangle::Draw(int _color)
{
	setcolor(_color);
	int x1 = x - width/2;
	int y1 = y - height/2;
	int x2 = x + width/2;
	int y2 = y + height/2;
	rectangle (x1, y1, x2, y2);
}

void Rectangle::Rotate()
{
     
	 int *arrc = new int (8);
	
		setcolor(0);
		
		arrc[0] = x - width/2;
		arrc[1] = y - height/2;
		arrc[2] = x - width/2;
		arrc[3] = y + height/2;
		arrc[4] = x + width/2;
		arrc[5] = y + height/2;
		arrc[6] = x + width/2;
		arrc[7] = y - height/2;
		
		drawpoly(4, arrc);
		
		setcolor(color);
		
		arrc[0] = x;
		arrc[1] = (int)(y - sqrt((width/2)*(width/2) + (height/2)*(height/2)));
		arrc[2] = (int)(x - sqrt((width/2)*(width/2) + (height/2)*(height/2)));
		arrc[3] = y;
		arrc[4] = x;
		arrc[5] = (int)(y + sqrt((width/2)*(width/2) + (height/2)*(height/2)));
		arrc[6] = (int)(x + sqrt((width/2)*(width/2) + (height/2)*(height/2)));
		arrc[7] = y;
		
		drawpoly(4, arrc);
		
		setcolor(0);
		
		drawpoly(4, arrc);
		
		setcolor(color);
		
		arrc[0] = x - width/2;
		arrc[1] = y - height/2;
		arrc[2] = x - width/2;
		arrc[3] = y + height/2;
		arrc[4] = x + width/2;
		arrc[5] = y + height/2;
		arrc[6] = x + width/2;
		arrc[7] = y - height/2;
		
		drawpoly(4, arrc);
}
