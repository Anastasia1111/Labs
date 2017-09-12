//#include "complex.cpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define PI 3.14159265359

struct complex
{
	double re;
	double im;
};

void fourier(double* f, complex* a, int n)
{
	for(int k=0; k<n; k++)
	{
		complex tmp; tmp.re = 0; tmp.im = 0;
		for(int j=0; j<n; j++)
		{
			complex exp;
			exp.re = cos(-2*k*j*PI/n);
			printf("re%d:%f\n",j,exp.re);
			exp.im = sin(-2*k*j*PI/n);
			printf("im%d:%f\n\n",j,exp.im);
			tmp.re += exp.re * f[j];
			tmp.im += exp.im * f[j];
		}
		a[k].re = tmp.re/(double)n;
		a[k].im = tmp.im/(double)n;
	}
}

void PrintMas(complex* A, int n)
{
	int i;
	printf("\nMassiv:\n");
	for (i = 0;i<n;i++) printf("(%f + %f i)\n", A[i].re, A[i].im);
}

int main()
{
	double f[] = {0, 1, 0, 1, 0};
	complex a[5];
	fourier(f, a, 5);
	PrintMas(a, 5);
	system("pause");
	return 0;
}
