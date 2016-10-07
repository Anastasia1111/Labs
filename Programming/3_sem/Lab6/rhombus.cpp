#include "rhombus.h"

void Rhombus::Draw(int _color)
{
	float kor = sqrt(3);
	float d = kor*side;
	
	setcolor(_color);
	int x1 = x;
	int y1 = y - side/2;
	int x2 = (int)(x - d/2);
	int y2 = y;
	int x3 = x;
	int y3 = y + side/2;
	int x4 = (int)(x + d/2);
	int y4 = y;
	line (x1, y1, x2, y2);
	line (x2, y2, x3, y3);
	line (x3, y3, x4, y4);
	line (x4, y4, x1, y1);
}

void Rhombus::Rotate()
{
	float kor = sqrt(3);
	float d = kor*side;
	
	int angle = 0;
	double endangle;
	double sinus, cosinus;
	
	int *arrc = new int (8);
	
	setcolor(0);
		
	endangle = angle * (3.14/30);
	sinus = sin(endangle);
	cosinus = cos(endangle);
	
	arrc[0] = (int)(x + d/2 * sinus);
	arrc[1] = (int)(y - side/2 * cosinus);
	arrc[2] = (int)(x - d/2 * cosinus);
	arrc[3] = (int)(y - side/2 * sinus);
	arrc[4] = (int)(x - d/2 * sinus);
	arrc[5] = (int)(y + side/2 * cosinus);
	arrc[6] = (int)(x + d/2 * cosinus);
	arrc[7] = (int)(y + side/2 * sinus);
	
	line (arrc[0], arrc[1],arrc[2],arrc[3]);
    line (arrc[2],arrc[3],arrc[4],arrc[5]);
	line (arrc[4],arrc[5],arrc[6],arrc[7]);
	line (arrc[6],arrc[7],arrc[0],arrc[1]);
	
	while(!kbhit()) {
		
		setcolor(color);
		
		angle++;
		if (angle > 30) angle = 0;
		
		endangle = angle * (3.14/30);
		sinus = sin(endangle);
		cosinus = cos(endangle);
		
		arrc[0] = (int)(x + d/2 * sinus);
		arrc[1] = (int)(y - side/2 * cosinus);
		arrc[2] = (int)(x - d/2 * cosinus);
		arrc[3] = (int)(y - side/2 * sinus);
		arrc[4] = (int)(x - d/2 * sinus);
		arrc[5] = (int)(y + side/2 * cosinus);
		arrc[6] = (int)(x + d/2 * cosinus);
		arrc[7] = (int)(y + side/2 * sinus);
		
		
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
        line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[6],arrc[7]);
		line (arrc[6],arrc[7],arrc[0],arrc[1]);
		delay(100);
		
		setcolor(0);
		
		endangle = angle * (3.14/30);
		sinus = sin(endangle);
		cosinus = cos(endangle);
		
		arrc[0] = (int)(x + d/2 * sinus);
		arrc[1] = (int)(y - side/2 * cosinus);
		arrc[2] = (int)(x - d/2 * cosinus);
		arrc[3] = (int)(y - side/2 * sinus);
		arrc[4] = (int)(x - d/2 * sinus);
		arrc[5] = (int)(y + side/2 * cosinus);
		arrc[6] = (int)(x + d/2 * cosinus);
		arrc[7] = (int)(y + side/2 * sinus);
		
		line (arrc[0], arrc[1],arrc[2],arrc[3]);
        line (arrc[2],arrc[3],arrc[4],arrc[5]);
		line (arrc[4],arrc[5],arrc[6],arrc[7]);
		line (arrc[6],arrc[7],arrc[0],arrc[1]);
    }
    getch();
    delete arrc;
}
