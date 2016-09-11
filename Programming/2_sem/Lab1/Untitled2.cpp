#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

float step(float x, int n)
{
    float s=1;
    int i, na;
    if (n==0) return 1;
    na=abs(n);
    for (i=0; i<na; i++) s*=x;
    if (n<0) s=1/s;
    return s;
}

main() {
    float x,res;
    int n;
	printf("x=");
	scanf("%f", &x);
	printf("n=");
	scanf("%d", &n);
	res=step(x,n);	   							
    printf ("%5.3f^%d=%f \n", x,n,res); 
    getch(); 
}
