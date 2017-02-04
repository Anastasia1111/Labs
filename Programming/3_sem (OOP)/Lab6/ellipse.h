#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Ellips : public Geometry
{
	public:
           
    		Ellips() : Geometry(), xradius(1), yradius(2)
			{};
    		
    		Ellips(int _x, int _y, int _color) : Geometry(_x, _y, _color), xradius(1), yradius(2) 
			{};
			
			Ellips(int _x, int _y, int _color, int _xradius, int _yradius) : Geometry(_x, _y, _color), xradius(_xradius), yradius(_yradius) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int xradius;
    		int yradius;

};

#endif
