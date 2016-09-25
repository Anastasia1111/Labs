#include "rhombus.h"

Rhombus::Rhombus()
{
	x = y = color = 0;
	side = 1;
}

void Rhombus::set(int _x, int _y, int _color, int _side)
{
	y = _y;
	x = _x;
	color = _color;
	side = _side;
}

void Rhombus::Draw(int _color)
{
	float kor = sqrt(3);
	float d = kor*side;
	
	setcolor(_color);
	int x1 = x;
	int y1 = y - side/2;
	int x2 = x - d/2;
	int y2 = y;
	int x3 = x;
	int y3 = y + side/2;
	int x4 = x + d/2;
	int y4 = y;
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x4, y4);
	line (x4, y4, x1, y1);
}

void Rhombus::Rotate()
{
}
