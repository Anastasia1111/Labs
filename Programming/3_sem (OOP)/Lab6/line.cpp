#include "line.h"

void Line::Draw(int _color)
{
	setcolor(_color);
	int x1 = x - length/2;
	int y1 = y;
	int x2 = x + length/2;
	int y2 = y;
	line (x1, y1, x2, y2);
}

void Line::Rotate()
{
	int angle = 0;
	int len = length/2;
	int *arrc = new int (4);
	double endangle;
	int lencos, lensin;
	setcolor(0);
	endangle = angle * (3.14/30);
	lencos = (int)(len * cos(endangle));
	lensin = (int)(len * sin(endangle));
	arrc[0] = x - lencos;
	arrc[1] = y - lensin; 
	arrc[2] = x + lencos;
	arrc[3] = y + lensin;
	drawpoly(2, arrc);
	while (!kbhit()) {
		setcolor(color);
		angle++;
		if (angle > 30) angle = 0;
		endangle = angle * (3.14/30);
		lencos = (int)(len * cos(endangle));
		lensin = (int)(len * sin(endangle));
		arrc[0] = x - lencos;
		arrc[1] = y - lensin; 
		arrc[2] = x + lencos;
		arrc[3] = y + lensin;
		drawpoly(2, arrc);
		delay(100);
		setcolor(0);
		endangle = angle * (3.14/30);
		lencos = (int)(len * cos(endangle));
		lensin = (int)(len * sin(endangle));
		arrc[0] = x - lencos;
		arrc[1] = y - lensin; 
		arrc[2] = x + lencos;
		arrc[3] = y + lensin;
		drawpoly(2, arrc);
	}
	getch();
	delete arrc;
}
