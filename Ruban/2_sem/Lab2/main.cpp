#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PI 3.14159265359

int T = 0;

struct complex
{
	double re;
	double im;
};

void DFT(double* f, complex* a, int n)
{
	for(int k=0; k<n; ++k)
	{
		a[k].re = 0;
		a[k].im = 0;
		for(int j=0; j<n; ++j)
		{
			a[k].re += cos(-2 * k * j * PI / n) * f[j];
			a[k].im += sin(-2 * k * j * PI / n) * f[j];
			T += 5;
		}
		a[k].re /= n;
		a[k].im /= n;
	}
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void FillRand(double* a, int n)
{
	srand(time(0));
	for (int i = 0; i<n; ++i)
		a[i] = fRand(-1.0 * n, 1.0 * n);
}

void Output(double* a, int n)
{
	printf("\nArray:\n");
	for (int i = 0; i<n; ++i)
		printf("%.3f ", a[i]);
	printf("\n");
}

void Output(complex* a, int n)
{
	printf("\nArray:\n");
	for (int i = 0; i<n; ++i)
		printf("(%.3f + %.3fi)\n", a[i].re, a[i].im);
	printf("T = %d\n", T);
}

int main()
{
	int n;
	printf("Array size: ");
	scanf("%d", &n);
	double *f = new double[n];
	complex *a = new complex[n];
	if (a == NULL || f == NULL) {
		printf("\nERROR\n");
		system("Pause");
		return 1;
	}
	FillRand(f, n);
	Output(f, n);
	DFT(f, a, n);
	Output(a, n);
	system("Pause");
	return 0;
}
