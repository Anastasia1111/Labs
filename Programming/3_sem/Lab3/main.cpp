#include <cstdlib>
#include <iostream>

#include "t_point.h"

using namespace std;

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
