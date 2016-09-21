#include <cstdlib>
#include <iostream>
#include <graphics.h>

#define ScreenWidth 800
#define ScreenHeight 600

using namespace std;

class tPoint 
{
	public:
           
    		tPoint(); 
    		
    		~tPoint();
    		
    		void setPoint();
    		
    		void Draw();
    		
    		void DirectMoving(int rBorder, int bBorder);
    		
    		void RandMoving(int rBorder, int bBorder);
		
	private:
            
    		int x;
    		int y;
    		int color;

};

tPoint::tPoint()
{
	x = y = color = 0;
} 
		
tPoint::~tPoint() 
{
                  
}

void tPoint::setPoint()
{
	y = rand()%ScreenHeight + 1;
	x = rand()%ScreenWidth + 1;
	color = rand()%15 + 1;	
}

void tPoint::Draw()
{
     putpixel(x,y, color);
}

void tPoint::DirectMoving(int rBorder, int bBorder)
{
        int logX = 1, logY = 1;
    	while (!kbhit()) {
                delay(25);
        		putpixel(x, y, 0);
        		x += logX;
        		y += logY;
        		putpixel(x, y, color);
        		if (x >= rBorder || x <= 0) logX *= (-1);
        		if (y >= bBorder || y <= 0) logY *= (-1);
    		
    	}
    	getch();
}

void tPoint::RandMoving(int rBorder, int bBorder)
{
        int logX = rand()%7 - 3, logY = rand()%7 - 3;
    	while (!kbhit()) {
                delay(25);
        		putpixel(x, y, 0);
        		x += logX;
        		y += logY;
        		putpixel(x, y, color);
        		if (x >= rBorder || x <= 0) logX = rand()%7 - 3;
        		if (y >= bBorder || y <= 0) logY = rand()%7 - 3;
    	}
    	getch();
}

int main(int argc, char *argv[])
{
    tPoint points[100];
    
    srand(time(0));
    
    initwindow(ScreenWidth, ScreenHeight, "Lab 3", 200, 0);
    
    for (int i = 0; i < 100; i++) {
        points[i].setPoint();
        points[i].Draw(); 
    }
    
    points[rand()%100].DirectMoving(ScreenWidth, ScreenHeight);
    points[rand()%100].RandMoving(ScreenWidth, ScreenHeight);
    
    system("PAUSE");	
	closegraph();
    return EXIT_SUCCESS;
}
