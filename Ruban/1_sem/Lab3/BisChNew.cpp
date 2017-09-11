#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double formula(double x)
{
	return -1 * pow(x, 2.0) + 4;
}

double derformula(double x)
{
	return -2 * x;
}

double der2formula(double x)
{
	return -2;
}

double a = 1;
double b = -17;
double accur = 0.000000001;
double newton = -7;

int main()
{
	int iternum = 0;
	
	double fa = formula(a);
	double fb = formula(b);
	if(fa * fb > 0)
	{
		printf("Bad segment!\n");
		system("pause");
		return 1;
	}
	else if(fa * fb == 0)
	{
		printf("One of segment's end is solution!\n");
		system("pause");
		return 0;
	}
	if(fa > fb)
	{
		double buf = a;
		a = b;
		b = buf;	
	}	
	
	printf("bisection:\n");
	double middle = (a + b)/2;
		
	while(fabs(b-a) >= accur)
	{
		++iternum;
		if(formula(middle) > 0)
			b = middle;
		else
			if(formula(middle) < 0)
				a = middle;
			else
				if(formula(middle) == 0)
				{
					printf("f(middle) = 0\n middle = %3.15f (%d step)\n", middle, iternum);
					system("pause");
					return 0;
				}
		middle = (a + b)/2;
	}
	printf("Accuracy is reached!\n middle = %3.15f (%d step)\n", middle, iternum);
	
	
	
	printf("\nchord:\n");
	double chordp = (a * fb - b * fa)/(fb - fa);
	iternum = 0;
	double prev = 0.0;
	
	while(fabs(chordp - prev) >= accur)
	{
		++iternum;
		if(formula(chordp) > 0)
			b = chordp;
		else
			if(formula(chordp) < 0)
				a = chordp;
			else
				if(formula(chordp) == 0)
				{
					printf("f(chordp) = 0\n chordp = %3.15f (%d step)\n", chordp, iternum);
					system("pause");
					return 0;
				}
		prev = chordp;
		chordp = (a * fb - b * fa)/(fb - fa);
	}
	printf("Accuracy is reached!\n chordp = %3.15f (%d step)\n", chordp, iternum);
	
	
	
	printf("\nNewton:\n");
	iternum = 0;
	prev = 0.0;
	if(formula(newton) * der2formula(newton) >= 0)
	{
		while(fabs(newton - prev) >= accur)
		{
			++iternum;
			prev = newton;
			newton = prev - (formula(prev)/derformula(prev));
		}
	} else {
		printf("Bad point.\n");
		system("pause");
		return 0;
	}
	printf("Accuracy is reached!\n newton = %3.15f (%d step)\n", newton, iternum);
	
	system("pause");
	return 0;
}
