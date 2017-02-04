#include "triangle.h"

void Triangle::Draw(int _color)
{
	float R = side*(sqrt(3)/3);
	float h = side*(sqrt(3)/2);
	
	setcolor(_color);
	int x1 = x;
	int y1 = (int)(y - R);
	int x2 = x - side/2;
	int y2 = (int)(y1 + h);
	int x3 = x + side/2;
	int y3 = y2;
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x1, y1);
}

void Triangle::Rotate()
{
	float R = side*(sqrt(3)/3);
	float h = side*(sqrt(3)/2);
	
	int angle = 0;
	double endangle, endangle1, endangle2;
	double sinus, cosinus;
	double sinus1, cosinus1;
	double sinus2, cosinus2;
	
	int *arrc = new int (6);
	
	
	while(!kbhit()) {
		
		setcolor(0);
	
		arrc[0] = x;
		arrc[1] = (int)(y - R);
		arrc[2] = x - side/2;
		arrc[3] = (int)(arrc[1] + h);
		arrc[4] = x + side/2;
		arrc[5] = arrc[3];
		
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
	    line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[0],arrc[1]);
		
		setcolor(color);

		arrc[0] = x;
		arrc[1] = (int)(y + R);
		arrc[2] = x - side/2;
		arrc[3] = (int)(arrc[1] - h);
		arrc[4] = x + side/2;
		arrc[5] = arrc[3];
			
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
        line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[0],arrc[1]);
		
		delay(100);
		
		setcolor(0);
		
		arrc[0] = x;
		arrc[1] = (int)(y + R);
		arrc[2] = x - side/2;
		arrc[3] = (int)(arrc[1] - h);
		arrc[4] = x + side/2;
		arrc[5] = arrc[3];
		
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
        line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[0],arrc[1]);
		
		setcolor(color);
	
		arrc[0] = x;
		arrc[1] = (int)(y - R);
		arrc[2] = x - side/2;
		arrc[3] = (int)(arrc[1] + h);
		arrc[4] = x + side/2;
		arrc[5] = arrc[3];
		
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
	    line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[0],arrc[1]);
		
		delay(100);
	}
	getch();
	delete arrc;
}
