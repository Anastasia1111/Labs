#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "complex.h"

#define PI 3.14159265359

void conv(Complex *a, Complex *b, Complex *c, int n);
void DFTconv(Complex *a, Complex *b, Complex *c, int n);
void SFFTconv(Complex *a, Complex *b, Complex *c, int n);

void DFT(Complex* f, Complex* a, int n);
void DFTInv(Complex *a, Complex *f, int n);

void SFFT(Complex* f, Complex* a, int n);
void SFFTInv(Complex* f, Complex* a, int n);

void random(Complex *a, int n);
double fRand(double fMin, double fMax);
void print_arr(Complex *a, int n);

int T;

int main(int argc, char const *argv[])
{
	srand(time(0));

	int n;
	n = 8;

	Complex *a = new Complex [n];
	Complex *b = new Complex [n];
	Complex *c = new Complex [n];
	random(a, n);
	random(b, n);

	printf("arr a:\n");
	print_arr(a,n);
	printf("arr b:\n");
	print_arr(b,n);

	/*DFT(a, c, n);
	printf("DFT:\n");
	printf("T = %d\n\n", T);
	print_arr(c, n);
	DFTInv(c, b, n);
	printf("DFTInv:\n");
	print_arr(b, n);
	printf("T = %d\n\n", T);

	SFFT(a, c, n);
	printf("SFFT:\n");
	printf("T = %d\n\n", T);
	print_arr(c, n);
	SFFTInv(c, b, n);
	printf("SFFTInv:\n");
	print_arr(b, n);
	printf("T = %d\n\n", T);*/

	conv(a, b, c, n);
	printf("Convolution...\narr c:\n");
	print_arr(c, 2*n-1);
	printf("T = %d\n\n", T);

	DFTconv(a, b, c, n);
	printf("Convolution with DFT...\narr c:\n");
	print_arr(c, 2*n-1);
	printf("T = %d\n\n", T);

	SFFTconv(a, b, c, n);
	printf("Convolution with SFFT...\narr c:\n");
	print_arr(c, 2*n-1);
	printf("T = %d\n\n", T);

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

void DFTconv(Complex *a, Complex *b, Complex *c, int n){
	int i;
	Complex *long_a = new Complex [2*n - 1];
	Complex *long_b = new Complex [2*n - 1];
	for(int i = 0; i < 2*n-1; ++i)
		c[i] = 0;
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
	{
		abuf[i] *= bbuf[i] * 2.0 * n; // now here should be an Fourier of convolution
		T += 2;
	}
	DFTInv (abuf, c, 2*n-1);
}

void SFFTconv(Complex *a, Complex *b, Complex *c, int n) 
{
	int i;
	Complex *long_a = new Complex [2*n - 1];
	Complex *long_b = new Complex [2*n - 1];
	for(int i = 0; i < 2*n-1; ++i)
		c[i] = 0;
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
	SFFT (long_a, abuf, 2*n-1);
	SFFT (long_b, bbuf, 2*n-1);
	for(i = 0; i < 2*n-1; ++i)
	{
		abuf[i] *= bbuf[i] * 2.0 * n; // now here should be an Fourier of convolution
		T += 2;
	}
	SFFTInv (abuf, c, 2*n-1);
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
			T += 5;
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
			T += 5;
		}
	}
}

void SFFT(Complex* f, Complex* a, int n)
{
	int p1, p2;
	p1 = (int)sqrt(n);
	while (n % p1)
		--p1;
	p2 = n/p1;
	Complex exp;
	Complex **a1 = new Complex *[p1];

	for(int k1=0; k1<p1; ++k1)
	{
		a1[k1] = new Complex [p2];
		for(int j2=0; j2<p2; ++j2)
		{
			a1[k1][j2].set(0, 0);
			for(int j1=0; j1<p1; ++j1)
			{
				exp.set(cos(-2.0 * k1 * j1 * PI / p1), sin(-2.0 * k1 * j1 * PI / p1));
				a1[k1][j2] += exp * f[j2 + p2 * j1];
				T += 5;
			}
			a1[k1][j2] /= p1;
		}
	}

	Complex **a2 = new Complex *[p1];
	for(int k1=0; k1<p1; ++k1)
	{
		a2[k1] = new Complex [p2];
		for(int k2=0; k2<p2; ++k2)
		{
			a2[k1][k2].set(0, 0);
			for(int j2=0; j2<p2; ++j2)
			{
				exp.set(cos(-2.0 * (k1 + p1*k2) * j2 * PI / n), sin(-2.0 * (k1 + p1*k2) * j2 * PI / n));
				a2[k1][k2] += exp * a1[k1][j2];
				T += 5;
			}
			a2[k1][k2] /= p2;
		}
	}

	for(int k = 0; k < n; ++k)
	{
		int k1 = k % p1;
		int k2 = k / p1;
		a[k] = a2[k1][k2];
	}
}

void SFFTInv(Complex* a, Complex* f, int n)
{
	int p1, p2;
	p1 = (int)sqrt(n);
	while (n % p1)
		--p1;
	p2 = n/p1;
	Complex exp;
	Complex **f1 = new Complex *[p1];

	for(int k1=0; k1<p1; ++k1)
	{
		f1[k1] = new Complex [p2];
		for(int j2=0; j2<p2; ++j2)
		{
			f1[k1][j2].set(0, 0);
			for(int j1=0; j1<p1; ++j1)
			{
				exp.set(cos(2.0 * k1 * j1 * PI / p1), sin(2.0 * k1 * j1 * PI / p1));
				f1[k1][j2] += exp * a[j2 + p2 * j1];
				T += 5;
			}
		}
	}

	Complex **f2 = new Complex *[p1];
	for(int k1=0; k1<p1; ++k1)
	{
		f2[k1] = new Complex [p2];
		for(int k2=0; k2<p2; ++k2)
		{
			f2[k1][k2].set(0, 0);
			for(int j2=0; j2<p2; ++j2)
			{
				exp.set(cos(2.0 * (k1 + p1*k2) * j2 * PI / n), sin(2.0 * (k1 + p1*k2) * j2 * PI / n));
				f2[k1][k2] += exp * f1[k1][j2];
				T += 5;
			}
		}
	}

	for(int k = 0; k < n; ++k)
	{
		int k1 = k % p1;
		int k2 = k / p1;
		f[k] = f2[k1][k2];
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
