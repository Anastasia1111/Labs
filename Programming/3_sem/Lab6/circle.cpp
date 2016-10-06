#include "circle.h"

Circle::Circle()
{
	x = y = color = 0;
	radius = 1;
}

void Circle::set(int _x, int _y, int _color, int _radius)
{
	y = _y;
	x = _x;
	color = _color;
	radius = _radius;
}

void Circle::Draw(int _color)
{
	setcolor(_color);
	circle(x, y, radius);
}

void Circle::Rotate()
{
}
