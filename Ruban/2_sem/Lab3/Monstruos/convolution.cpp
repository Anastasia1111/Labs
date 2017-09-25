#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "complex.h"

#define PI 3.14159265359

void conv (Complex *a, Complex *b, Complex *c, int n);
void random (Complex *a, int n);
double fRand (double fMin, double fMax);
void print_arr (Complex *a, int n);

void DFT(Complex* f, Complex* a, int n);
void DFTInv (Complex *a, Complex *f, int n);

int T;

int main(int argc, char const *argv[])
{
	int n;
	n = 8;
	double fd[] = {0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};
	Complex *f = new Complex[n];
	for(int i = 0; i < n; ++i)
		f[i] = fd[i];
	Complex* a = new Complex[n];
	Complex* fi = new Complex[n];
	if (a == NULL || f == NULL || fi == NULL) {
		printf("\nERROR\n");
		system("Pause");
		return 1;
	}
	//FillRand(f, n);
	print_arr(f, n);
	DFT(f, a, n);
	print_arr(a, n);
	// SFFT(f, a, n);
	// print_arr(a, n);
	// FFT(f, a, n);
	// print_arr(a, n);
	printf("-----InvertedFT-----\n");
	DFTInv(a, fi, n);
	print_arr(fi, n);
	// SFFTInv(a, fi, n);
	// print_arr(fi, n);
	//FFTInv(a, fi, n);
	// print_arr(fi, n);


	/*Complex *a = new Complex [n];
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
	printf("T = %d", T);*/
	system("Pause");
	return 0;
}

void conv (Complex *a, Complex *b, Complex *c, int n)
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

void random (Complex *a, int n)
{
	srand(time(0));
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

void DFT(Complex* f, Complex* a, int n)
{
	T = 0;
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

void DFTInv (Complex *a, Complex *f, int n)
{
	T = 0;
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
