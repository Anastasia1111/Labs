#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
const int N = 10;
//const int N = 100;
//const int N = 1000;

main (){
    int i;
	float F[N+1], ft, fs, h, x;
	float a=0.2, b=10;
	h=(b-a)/N;
    printf("\n Ishodnie znacheniya F(x):\n");
	x=a;	
	for (i=0; i<=N; i++) {
        F[i]=sqrt(((2+x)*(2+x)*(2+x))/(x*x));
        printf("%3.2f  ",F[i]);
		x+=h;
    }
    ft=(F[0]+F[N])/2;
    printf("\n I1=");
    for (i=1; i<N; i++) ft+=F[i]; 
    ft*=h;
    printf("%3.2f  ",ft);
    fs=F[0]+F[N];
    printf("\n I2=");
    for (i=1; i<N; i++) 
	    if (i%2) { fs+=F[i]*4; }
	    else { fs+=F[i]*2; }
    fs*=h/3;
    printf("%3.2f  ",fs); 
    if (ft==fs) printf("\n I1=I2");
    if (ft<fs) printf("\n I1<I2");
    if (ft>fs) printf("\n I1>I2");
	getch();
}
        
