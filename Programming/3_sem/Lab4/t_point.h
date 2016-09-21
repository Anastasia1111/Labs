#ifndef T_POINT
#define T_POINT

#include <cstdlib>
#include <graphics.h>

#define ScreenWidth 800
#define ScreenHeight 600

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

#endif
