
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#define e 0.001

main() {
    float s,x,t,y;
    int i;
	printf("x=");
	scanf("%f", &x);
    s=-x;   						
    i=y=1;						
    do {
	    i++; 
        y*=i;
        t=pow(-1,i)*pow(x,i)/y;
        s+=t; 
    }
    while (fabs(t)>=e); 	   							
    printf ("s=%5.3f \n", s);   
    getch(); 
}
