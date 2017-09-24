#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "complex.h++"

void conv (double *a, double *b, double *c, int n);
void conv (Complex *a, Complex *b, Complex *c, int n);
void random (double *a, int n);
void random (Complex *a, int n);
double fRand(double fMin, double fMax);
void print_arr (double *a, int n);
void print_arr (Complex *a, int n);

int T;

int main(int argc, char const *argv[])
{
	srand(time(0));
	
	int n = 10;
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
	printf("T = %d", T);
	system("pause");
	return 0;
}

void conv (double *a, double*b, double *c, int n)
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

void random (double *a, int n)
{
	for(int i = 0; i < n; ++i)
		a[i] = fRand(-1*n, n);
}

void print_arr (double *a, int n)
{
	for(int i = 0; i < n; ++i)
		printf("[%d] = %2.4f\n", i, a[i]);
	printf("\n"); 
}

void random (Complex *a, int n)
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
