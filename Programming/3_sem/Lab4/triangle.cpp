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
	int y1 = (int)(y - R);
	int x2 = x - side/2;
	int y2 = (int)(y1 + h);
	int x3 = x + side/2;
	int y3 = y2;
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x1, y1);
}

void Triangle::Rotate()
{
	float R = side*(sqrt(3)/3);
	
	int angle = 0;
	double endangle, endangle1;
	double sinus, cosinus;
	double sinus1, cosinus1;
	double sinus2, cosinus2;
	
	int *arrc = new int (6);
	
		setcolor(0);
		
		endangle = angle * (3.14/30);
		endangle1 = (angle + 12) * (3.14/30);
		endangle2 = (angle + 4) * (3.14/30);
		if (angle >= 18) endangle1 = (angle - 18) * (3.14/30);
		if (angle >= 26) endangle2 = (angle - 26) * (3.14/30);
		
		sinus = sin(endangle);
		cosinus = cos(endangle);
		sinus1 = sin(endangle1);
		cosinus1 = cos(endangle1);
		sinus2 = sin(endangle2);
		cosinus2 = cos(endangle2);
		
		arrc[0] = x + side/2 * sinus;
		arrc[1] = (int)(y - R * cosinus);
		arrc[2] = x - side/2 * sinus1;
		arrc[3] = (int)(y - R + (R+h) * cosinus1);
		arrc[4] = x + side/2 * sinus2;
		arrc[5] = y - R + (R+h) * cosinus2;
		
		drawpoly(3, arrc);
		
		setcolor(color);
		
		angle++;
		if (angle > 30) angle = 0;
		
		endangle = angle * (3.14/30);
		endangle1 = (angle + 12) * (3.14/30);
		endangle2 = (angle + 4) * (3.14/30);
		if (angle >= 18) endangle1 = (angle - 18) * (3.14/30);
		if (angle >= 26) endangle2 = (angle - 26) * (3.14/30);
		
		sinus = sin(endangle);
		cosinus = cos(endangle);
		sinus1 = sin(endangle1);
		cosinus1 = cos(endangle1);
		sinus2 = sin(endangle2);
		cosinus2 = cos(endangle2);
		
		arrc[0] = x + side/2 * sinus;
		arrc[1] = (int)(y - R * cosinus);
		arrc[2] = x - side/2 * sinus1;
		arrc[3] = (int)(y + R * cosinus1);
		arrc[4] = x + side/2 * sinus2;
		arrc[5] = y + R * cosinus2;
		
		drawpoly(4, arrc);
}
