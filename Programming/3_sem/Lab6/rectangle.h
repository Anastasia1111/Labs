#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdlib>
#include <graphics.h>
#include <cmath>

#include "geometry.h"

class Rectangle : public Geometry
{
	public:
           
    		Rectangle() : Geometry(), height(1), width(1)
			{};
    		
    		Rectangle(int _x, int _y, int _color) : Geometry( _x, _y, _color), height(1), width(1)
			{};
    		
    		Rectangle(int _x, int _y, int _color, int _height, int _width) : Geometry( _x,  _y,  _color), height(_height), width(_width)
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int height;
    		int width;

};

#endif
