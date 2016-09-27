#include "ellipse.h"

Ellipse::Ellipse()
{
	x = y = color = 0;
	xradius = 1;
	yradius = 2;
}

void Ellipse::set(int _x, int _y, int _color, int _xradius, int _yradius)
{
	y = _y;
	x = _x;
	color = _color;
	xradius = _xradius;
	yradius = _yradius;
}

void Ellipse::Draw(int _color)
{
	setcolor(_color);
	ellipse(x, y, 0, 360, xradius, yradius);
}

void Ellipse::Rotate()
{
	setcolor(0);
	
	ellipse(x, y, 0, 360, xradius, yradius);
	
	setcolor(color);
	int buff = xradius;
	xradius = yradius;
	yradius = buff;
	
	ellipse(x, y, 0, 360, xradius, yradius);
}
