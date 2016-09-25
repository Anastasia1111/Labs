#ifndef CIRCLE_H
#define CIRCLE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Circle : Geometry
{
	public:
           
    		Circle();
    		
    		void set(int _x, int _y, int _color, int _length);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int radius;

};

#endif
