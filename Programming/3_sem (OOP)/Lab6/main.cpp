#include <cstdlib>
#include <iostream>

#include "geometry.h"
#include "line.h"
#include "rhombus.h"
#include "ellipse.h"
#include "triangle.h"

using namespace std;

int main(int argc, char *argv[])
{
	Geometry** fig = new Geometry* [4];
	
	srand(time(0));
    
    int x = rand()%ScreenWidth + 1;
    int y = rand()%ScreenHeight + 1;
    int color = rand()%15 + 1;
    int length = rand()%200 + 50;
	
    fig[0] = new Line(x, y, color, length);
    fig[1] = new Rhombus(x, y, color, length);
    fig[2] = new Ellips(x, y, color, length/2, length);
    fig[3] = new Triangle(x, y, color, length);
    
    initwindow(ScreenWidth, ScreenHeight, "Lab 6", 200, 0);
    
    fig[0]->Draw(color);
    
    delay(50);
    
    fig[0]->Rotate();
    
    fig[1]->Draw(color);
    
    delay(50);
    
    fig[1]->Rotate();
    
    fig[2]->Draw(color);
    
    delay(50);
    
    fig[2]->Rotate();
    
    fig[3]->Draw(color);
    
    delay(50);
    
    fig[3]->Rotate();
    
    closegraph();
    //system("PAUSE");	
    
    delete[] fig;
	
    return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
