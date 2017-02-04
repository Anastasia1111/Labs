#ifndef LINE_H
#define LINE_H

#include <cstdlib>
#include <graphics.h>
#include <math.h>

#include "geometry.h"

class Line : public Geometry
{
	public:
           
    		Line();
    		
    		void set(int _x, int _y, int _color, int _length);
    		
    		void Draw(int _color);
    		
    		void Rotate();
		
	private:
            
    		int length;

};

#endif
