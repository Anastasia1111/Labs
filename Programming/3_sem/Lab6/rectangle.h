#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdlib>
#include <graphics.h>
#include <cmath>

#include "geometry.h"

class Rectangle : public Geometry
{
	public:
           
    		Rectangle();
    		
    		Rectangle(int _x, int _y, int _color) : Geometry( _x, _y, _color) 
			{};
    		
    		void set(int _x, int _y, int _color, int _height, int _width);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int height;
    		int width;

};

#endif
