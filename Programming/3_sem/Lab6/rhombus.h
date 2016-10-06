#ifndef RHOMBUS_H
#define RHOMBUS_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Rhombus : public Geometry
{
	public:
           
    		Rhombus();
    		
    		Rhombus(int _x, int _y, int _color) : Geometry( _x,  _y,  _color) 
			{};
    		
    		void set(int _x, int _y, int _color, int _side);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int side;
    		

};

#endif
