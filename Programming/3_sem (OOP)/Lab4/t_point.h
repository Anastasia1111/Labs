#ifndef T_POINT_H
#define T_POINT_H

#include <cstdlib>
#include <graphics.h>

#include "geometry.h"

class tPoint : Geometry
{
	public:
           
    		tPoint() : Geometry()
			{
			};
    		
    		void Draw(int _color);
    		
    		void Rotate();

};

#endif
