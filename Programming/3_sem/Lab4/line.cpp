#include "line.h"

Line::Line()
{
	x = y = color = 0;
	length = 1;
}

void Line::set(int _x, int _y, int _color, int _length)
{
	y = _y;
	x = _x;
	color = _color;
	length = _length;
}

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
	int endangle;
	int lencos, lensin;
	while (!kbhit()) {
		setcolor(0);
		endangle = (int)(angle * (M_PI/30));
		lencos = (int)(len * cos(endangle));
		lensin = (int)(len * sin(endangle));
		arrc[0] = x - lencos;
		arrc[1] = y - lensin; 
		arrc[2] = x + lencos;
		arrc[3] = y + lensin;
		drawpoly(2, arrc);
		setcolor(color);
		angle++;
		if (angle > 5) angle = 0;
		endangle = (int)(angle * (M_PI/30));
		lencos = (int)(len * cos(endangle));
		lensin = (int)(len * sin(endangle));
		arrc[0] = x - lencos;
		arrc[1] = y - lensin; 
		arrc[2] = x + lencos;
		arrc[3] = y + lensin;
		drawpoly(2, arrc);
	}
	getch();
}
