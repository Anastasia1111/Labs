#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Triangle : Geometry
{
	public:
           
    		Triangle();
    		
    		void set(int _x, int _y, int _color, int _side);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int side;

};

#endif
