#include "ellipse.h"

Ellips::Ellips()
{
	x = y = color = 0;
	xradius = 1;
	yradius = 2;
}

void Ellips::set(int _x, int _y, int _color, int _xradius, int _yradius)
{
	y = _y;
	x = _x;
	color = _color;
	xradius = _xradius;
	yradius = _yradius;
}

void Ellips::Draw(int _color)
{
	setcolor(_color);
	ellipse(x, y, 0, 360, xradius, yradius);
}

void Ellips::Rotate()
{
	setcolor(0);
	ellipse(x, y, 0, 360, xradius, yradius);
	while (!kbhit()) {
		setcolor(color);
		int buff = xradius;
		xradius = yradius;
		yradius = buff;
		
		ellipse(x, y, 0, 360, xradius, yradius);
		delay(250);
		
		setcolor(0);
		ellipse(x, y, 0, 360, xradius, yradius);
	}
	getch();
}
