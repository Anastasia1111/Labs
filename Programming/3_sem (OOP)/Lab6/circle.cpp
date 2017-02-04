#include "circle.h"

void Circle::Draw(int _color)
{
	setcolor(_color);
	circle(x, y, radius);
}

void Circle::Rotate()
{
}
