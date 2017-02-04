#ifndef CIRCLE_H
#define CIRCLE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Circle : public Geometry
{
	public:
           
    		Circle() : Geometry(), radius(1)
			{};
    		
    		Circle(int _x, int _y, int _color) : Geometry( _x,  _y,  _color), radius(1) 
			{};
    		
    		Circle(int _x, int _y, int _color, int _radius) : Geometry( _x,  _y,  _color), radius(_radius) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int radius;

};

#endif
