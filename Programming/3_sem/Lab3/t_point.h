#ifndef T_POINT
#define T_POINT

#include <cstdlib>
#include <graphics.h>

class tPoint 
{
	public:
           
    		tPoint();
    		
    		~tPoint();
    		
    		void setPoint();
    		
    		void LineMoving(int rBorder, int bBorder);
    		
    		void RandMoving(int rBorder, int bBorder);
		
	private:
            
    		int x;
    		int y;
    		int color;

};

#endif
