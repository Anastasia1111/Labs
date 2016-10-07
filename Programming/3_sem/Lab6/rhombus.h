#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Rhombus : public Geometry
{
	public:
           
    		Rhombus() : Geometry(), side(1)
			{};
    		
    		Rhombus(int _x, int _y, int _color) : Geometry( _x,  _y,  _color), side(1) 
			{};
    		
    		Rhombus(int _x, int _y, int _color, int _side) : Geometry( _x,  _y,  _color), side(_side) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int side;
    		

};

#endif
