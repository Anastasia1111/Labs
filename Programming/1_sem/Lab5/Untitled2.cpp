#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
	double y,x,a,b,c,min,max,h,st,ed;
	a=2.14;  b=-4.21;  c=3.25; st=-4.5; ed=-13.5; h=0.5; 
	x=st;
	y=(a*x*x+b*x+c)*sin(x); min=y; max=y;
	while (x>=ed)
	{
		y=(a*x*x+b*x+c)*sin(x);
		if (y>max) {
			max=y;
		}
		if (y<min) {
			min=y;
		}
		x-=h;
	}
	printf("min=%7.3f, max=%7.3f", min,max);
	getch();
}
        
