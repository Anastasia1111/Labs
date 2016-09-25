#include "rectangle.h"

Rectangle::Rectangle()
{
	x = y = color = 0;
	width = height = 1;
}

void Rectangle::set(int _x, int _y, int _color, int _height, int _width)
{
	y = _y;
	x = _x;
	color = _color;
	width = _width;
	height = _height;
}

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
}
