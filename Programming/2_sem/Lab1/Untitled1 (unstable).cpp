#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

const double eps=0.0001;

double cosinus(double x)
{
    double e, s;
    int z,i;
    e=1; z=-1; i=2; s=1;
    while (e>eps) {
        e=(e*x*x)/(i*(i-1));
//        s*=-1*x*x/((2*n-1)*(2*n));
        i=i+2;
        s=s+e*z;
//        На втором шаге имеем: Сумм=1-(х^2/2!)
//        На третьем: Сумм=1-(х^2/2!)+(х^4/4!)
        z=-z;
    }
    return s;
}

main() {
    double  cost;
    float x;
	printf("x=");
	scanf("%f", &x);
    cost=cosinus(x);	   							
    printf ("Cos(%f)=%8.5f \n", x,cost); 
    printf ("Coscomp(%f)=%8.5f \n", x,cos(x));  
    getch(); 
}
