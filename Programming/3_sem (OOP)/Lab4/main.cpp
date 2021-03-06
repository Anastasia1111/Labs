#include <cstdlib>
#include <iostream>

#include "line.h"
#include "rhombus.h"
#include "ellipse.h"
#include "triangle.h"

using namespace std;

int main(int argc, char *argv[])
{
    Line line;
    Rhombus rhom;
    Ellips ellip;
    Triangle tri;
    
    srand(time(0));
    
    int x = rand()%ScreenWidth + 1;
    int y = rand()%ScreenHeight + 1;
    int color = rand()%15 + 1;
    int length = rand()%200 + 50;
    
    initwindow(ScreenWidth, ScreenHeight, "Lab 4", 200, 0);
    
    line.set(x, y, color, length);
    line.Draw(color);
    
    delay(50);
    
    line.Rotate();
    
    rhom.set(x, y, color, length);
    rhom.Draw(color);
    
    delay(50);
    
    rhom.Rotate();
    
    ellip.set(x, y, color, length/2, length);
    ellip.Draw(color);
    
    delay(50);
    
    ellip.Rotate();
    
    tri.set(x, y, color, length);
    tri.Draw(color);
    
    delay(50);
    
    tri.Rotate();
    
    closegraph();
    //system("PAUSE");	
	
    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
