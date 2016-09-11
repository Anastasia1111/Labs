#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

float step(float x, int n)
{
    float s;
    if (n==0) s=1;
    if (n<0) s=1/step(x,-n);
    if (n>0) s=x*step(x,n-1);
    return s;
}

main() {
    float a,c,z;
    int b;
	printf("a=");
	scanf("%f", &a);
	printf("c=");
	scanf("%f", &c);
	printf("b=");
	scanf("%d", &b);
	z=step(a,b)+step(c,b);	   							
    printf ("%5.3f^%d+%5.3f^%d=%f \n", a,b,c,b,z); 
    getch(); 
}
