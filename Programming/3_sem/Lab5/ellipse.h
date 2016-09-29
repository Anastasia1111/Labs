#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Ellips : Geometry
{
	public:
           
    		Ellips();
    		
    		void set(int _x, int _y, int _color, int _xradius, int _yradius);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int xradius;
    		int yradius;

};

#endif
