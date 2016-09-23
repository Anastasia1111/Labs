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
	int x1 = x - length/2;
	int y1 = y;
	int x2 = x + length/2;
	int y2 = y;
	line (x1, y1, x2, y2);
}

void Line::Rotate()
{
	// drawpoly ( int num+1 ,  int array ) 
}
