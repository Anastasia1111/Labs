#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Triangle : public Geometry
{
	public:
           
    		Triangle() : Geometry(), side(1)
			{};
    		
    		Triangle(int _x, int _y, int _color) : Geometry( _x,  _y,  _color), side(1) 
			{};
    		
    		Triangle(int _x, int _y, int _color, int _side) : Geometry( _x,  _y,  _color), side(_side) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int side;

};

#endif
