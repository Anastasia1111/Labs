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
           
    		Geometry() : x(0), y(0), color(0)
			{};
    		
    		Geometry(int _x, int _y, int _color) : x(_x), y(_y), color(_color)
			{};
    		
    		void DirectMoving(int rBorder, int bBorder);
    		
    		void RandMoving(int rBorder, int bBorder);
    		
    		virtual void Rotate()
			{
			};
			
			virtual void Draw(int _color)
			{
			};
		
	protected:
            
    		int x;
    		int y;
    		int color;

};

#endif
