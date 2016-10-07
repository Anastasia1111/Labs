#include "ellipse.h"

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
