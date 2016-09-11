#include <stdio.h>
#include <conio.h>
#include <math.h>

main (){
	int n,pn,py,y;
	float x,s,ps;
	printf("x=");
	scanf("%f", &x); n=1; s=1.; y=1.;
	ps=s; pn=n; py=y;
	while (fabs(ps)>0.001)
	{
		py=pn*py;
		ps=pow(-1,pn)*pow(x,pn)/py;
		pn=pn+1;
		printf("s=(-1)^%d*(%2.1f^%d)/%d!=%f %d!=%d\n",pn-1,x,pn-1,pn-1,ps,pn-1,py);
	}
	printf("pn(kon)=%d ps(kon)=%f \n",pn,ps);
	while (n<=pn)
	{
		y=n*y;
		s=s+pow(-1,n)*pow(x,n)/y;
		n=n+1;
	}
	printf("S=%f", s);
	getch();
}
        
