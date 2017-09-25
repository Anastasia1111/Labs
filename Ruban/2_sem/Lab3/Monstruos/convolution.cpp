#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "complex.h"

#define PI 3.14159265359

void conv(Complex *a, Complex *b, Complex *c, int n);
void Fconv(Complex *a, Complex *b, Complex *c, int n);

void DFT(Complex* f, Complex* a, int n);
void DFTInv(Complex *a, Complex *f, int n);

void random(Complex *a, int n);
double fRand(double fMin, double fMax);
void print_arr(Complex *a, int n);

int T;

int main(int argc, char const *argv[])
{
	srand(time(0));

	int n;
	n = 40;

	Complex *a = new Complex [n];
	Complex *b = new Complex [n];
	Complex *c = new Complex [2*n - 1];
	random(a, n);
	random(b, n);
	printf("arr a:\n");
	print_arr(a,n);
	printf("arr b:\n");
	print_arr(b,n);
	conv(a, b, c, n);
	printf("Convolution...\narr c:\n");
	print_arr(c,2*n-1);
	printf("T = %d\n", T);
	Fconv(a, b, c, n);
	printf("Convolution with DFT...\narr c:\n");
	print_arr(c,2*n-1);
	printf("T = %d\n", T);
	system("Pause");
	return 0;
}

void conv(Complex *a, Complex *b, Complex *c, int n)
{
	T = 0;
	for(int i = 0; i < 2*n-1; ++i)
		c[i] = 0;

	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			c[i+j] += a[i]*b[j];
			T++; 
		}
}

void Fconv(Complex *a, Complex *b, Complex *c, int n) {
	T = 0;
	int i;
	Complex *long_a = new Complex [2*n - 1];
	Complex *long_b = new Complex [2*n - 1];
	for(i = 0; i < n; ++i)
	{
		long_a[i] = a[i];
		long_b[i] = b[i];
	}
	for(i = n; i < 2*n - 1; ++i)
	{
		long_a[i] = 0.0;
		long_b[i] = 0.0;
	}

	Complex *abuf = new Complex [2*n - 1];
	Complex *bbuf = new Complex [2*n - 1];
	DFT (long_a, abuf, 2*n-1);
	DFT (long_b, bbuf, 2*n-1);
	for(i = 0; i < 2*n-1; ++i)
		abuf[i] *= bbuf[i] * 2.0 * n; // now here should be an Fourier of convolution
	DFTInv (abuf, c, 2*n-1);
}

void DFT(Complex* f, Complex* a, int n)
{
	Complex buf;
	for(int k=0; k<n; ++k)
	{
		a[k].set(0, 0);
		for(int j=0; j<n; ++j)
		{
			buf.set(cos(-2.0 * k * j * PI / n), sin(-2.0 * k * j * PI / n));
			a[k] += f[j] * buf;
			++T;
		}
		a[k] /= n;
	}
}

void DFTInv(Complex *a, Complex *f, int n)
{
	Complex buf;
	for(int k=0; k<n; ++k)
	{
		f[k].set(0, 0);
		for(int j=0; j<n; ++j)
		{
			buf.set(cos(2.0 * k * j * PI / n), sin(2.0 * k * j * PI / n));
			f[k] += (buf * a[j]);
			++T;
		}
	}
}

void random(Complex *a, int n)
{
	for(int i = 0; i < n; ++i)
		a[i].set(fRand(-1*n, n), fRand(-1*n, n));
}

void print_arr (Complex *a, int n)
{
	for(int i = 0; i < n; ++i) {
		a[i].print();
		printf("\n");
	}
	printf("\n");
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
