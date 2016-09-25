#include "triangle.h"

Triangle::Triangle()
{
	x = y = color = 0;
	side = 1;
}

void Triangle::set(int _x, int _y, int _color, int _side)
{
	y = _y;
	x = _x;
	color = _color;
	side = _side;
}

void Triangle::Draw(int _color)
{
	float R = side*(sqrt(3)/3);
	float h = side*(sqrt(3)/2);
	
	setcolor(_color);
	int x1 = x;
	int y1 = y - R;
	int x2 = x - side/2;
	int y2 = y1 + h;
	int x3 = x + side/2;
	int y3 = y2;
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x1, y1);
}

void Triangle::Rotate()
{
}
