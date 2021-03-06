#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#define ScreenWidth 800
#define ScreenHeight 600

class Geometry 
{
	public:
           
    		Geometry();
    		
    		void set(int _x, int _y, int _color);
    		
    		void DirectMoving(int rBorder, int bBorder);
    		
    		void RandMoving(int rBorder, int bBorder);
    		
    		virtual void Rotate()
			{
			};
			
			void Draw(int _color)
			{
			};
		
	protected:
            
    		int x;
    		int y;
    		int color;

};

#endif
