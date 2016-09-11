#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
	int i;
	float s,k,l,x;
	s=1; k=0; l=0;
	while (i<=3)
	{
		k=i+2; l=i+3;
		x=k*l;
		s=s+1/pow(-x,i+1);
		i=i+1;
	}
	printf("S=%6.5f", s);
	getch();
}
        
