#include <cstdlib>
#include <iostream>

#include "line.h"
#include "rhombus.h"
#include "ellipse.h"
#include "triangle.h"

using namespace std;

int main(int argc, char *argv[])
{
    Line* line = new Line[10];
    Rhombus* rhom = new Rhombus[10];
    Ellips* ellip = new Ellips[10];
    Triangle* tri = new Triangle[10];
    
    srand(time(0));
    
    int x = rand()%ScreenWidth + 1;
    int y = rand()%ScreenHeight + 1;
    int color = rand()%15 + 1;
    int length = rand()%200 + 50;
    
    initwindow(ScreenWidth, ScreenHeight, "Lab 5", 200, 0);
    
    line[0].set(x, y, color, length);
    line[0].Draw(color);
    
    delay(50);
    
    line[0].Rotate();
    
    rhom[0].set(x, y, color, length);
    rhom[0].Draw(color);
    
    delay(50);
    
    rhom[0].Rotate();
    
    ellip[0].set(x, y, color, length/2, length);
    ellip[0].Draw(color);
    
    delay(50);
    
    ellip[0].Rotate();
    
    tri[0].set(x, y, color, length);
    tri[0].Draw(color);
    
    delay(50);
    
    tri[0].Rotate();
    
    closegraph();
    //system("PAUSE");	
    
    delete line;
    delete rhom;
    delete ellip;
    delete tri;
	
    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
