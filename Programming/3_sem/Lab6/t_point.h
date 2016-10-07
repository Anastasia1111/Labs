#ifndef T_POINT_H
#define T_POINT_H

#include <cstdlib>
#include <graphics.h>

#include "geometry.h"

class tPoint : public Geometry
{
	public:
           
    		tPoint() : Geometry()
			{};
			
			tPoint(int _x, int _y, int _color) : Geometry( _x,  _y,  _color) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();

};

#endif
