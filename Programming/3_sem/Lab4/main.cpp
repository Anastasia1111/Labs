#include <cstdlib>
#include <iostream>

#include "line.h"

using namespace std;

int main(int argc, char *argv[])
{
    Line line;
    
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
    
    system("PAUSE");	
	closegraph();
    return EXIT_SUCCESS;
}
