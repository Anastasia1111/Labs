#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

const float eps=0.0001;

float cosinus(float x)
{
    float s, sum;
    int n;
    n=1;
    s=1;
    sum=0;
    do
    {
        sum+=s;
        s*=-1*x*x/((2*n-1)*(2*n));
        n++;
    }
    while (fabs(s)>eps);
    return sum;
}

main() {
    float x, cost;
	printf("x=");
	scanf("%f", &x);
    cost=cosinus(x);	   							
    printf ("Cos=%8.5f \n", cost); 
    printf ("Cos(comp)=%8.5f \n", cos(x));  
    getch(); 
}
