#ifndef LINE_H
#define LINE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Line : public Geometry
{
	public:
           
    		Line() : Geometry(), length(1)
			{};
    		
    		Line(int _x, int _y, int _color) : Geometry(_x, _y, _color), length(1) 
			{};

			Line(int _x, int _y, int _color, int _length) : Geometry(_x, _y, _color), length(_length) 
			{};
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int length;

};

#endif
