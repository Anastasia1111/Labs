#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define PI 3.14159265359

int T;

struct complex
{
	double re;
	double im;
};

void DFT(double* f, complex* a, int n)
{
	T = 0;
	
	for(int k=0; k<n; ++k)
	{
		a[k].re = 0;
		a[k].im = 0;
		for(int j=0; j<n; ++j)
		{
			a[k].re += cos(-2.0 * k * j * PI / n) * f[j];
			a[k].im += sin(-2.0 * k * j * PI / n) * f[j];
			++T;
		}
		a[k].re /= n;
		a[k].im /= n;
	}
}	

void SFFT(double* f, complex* a, int n)
{
	T = 0;
	
	int p1, p2;
	p1 = sqrt(n);
	while (n % p1)
		--p1;
	p2 = n/p1;
	
	for(int k=0; k<n; ++k)
	{
		int k1 = k % p1,
			k2 = k / p1;
		a[k].re = 0;
		a[k].im = 0;
		for(int j2=0; j2<p2; ++j2)
		{
			complex a1;
			a1.re = 0;
			a1.im = 0;
			for(int j1=0; j1<p1; ++j1)
			{
				a1.re += cos(-2.0 * k1 * j1 * PI / p1) * f[j2 + p2 * j1];
				a1.im += sin(-2.0 * k1 * j1 * PI / p1) * f[j2 + p2 * j1];
			}
			complex exp;
			exp.re = cos(-2.0 * (k1 + p1 * k2) * j2 * PI / (p1 * p2));
			exp.im = sin(-2.0 * (k1 + p1 * k2) * j2 * PI / (p1 * p2));
			a[k].re += (a1.re * exp.re - a1.im * exp.im) / p1;
			a[k].im += (a1.re * exp.im + a1.im * exp.re) / p1;
		}
		a[k].re /= p2;
		a[k].im /= p2;
	}
	T = n * (p1 + p2);
}

complex As(double* f, int* k, int s, int jsum, int add)
{
	complex res;
	if (s == 0)
	{
		res.re = f[jsum];
		res.im = 0;
	} else {
		res = As(f, k, s - 1, jsum, add * 2);
		complex tmp = As(f, k, s - 1, jsum + add, add * 2);
		complex exp;
		double power = 0;
		for (int l=0; l<s; ++l)
			power += k[l] * (2 << l);
		power *= -2.0 * PI /(2 << s);
		exp.re = cos(power);
		exp.im = sin(power);
		res.re += tmp.re * exp.re - tmp.im * exp.im;
		res.re /= 2;
		res.im += tmp.re * exp.im + tmp.im * exp.re;
		res.im /= 2;
	}
	return res;
}

void FFT(double* f, complex* a, int n)
{
	T = 0;
	
	int r = log2(n);
	int* k = new int[r];
	for(int km=0; km<n; ++km)
	{
		a[km].re = 0;
		a[km].im = 0;
		int kt = km;
		for(int l=0; l<r; ++l)
		{
			k[l] = kt % 2;
			kt /= 2;
		}
		a[km] = As(f, k, r, 0, 1);
	}
	T = n * r;
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void FillRand(double* a, int n)
{
	srand(time(0));
	for (int i=0; i<n; ++i)
		a[i] = fRand(-1.0 * n, 1.0 * n);
}

void Output(double* a, int n)
{
	printf("\nArray:\n");
	for (int i=0; i<n; ++i)
		printf("%.3f ", a[i]);
	printf("\n");
}

void Output(complex* a, int n)
{
	printf("\nArray:\n");
	for (int i=0; i<n; ++i)
		printf("(%.3f + %.3fi)\n", a[i].re, a[i].im);
	printf("T = %d*C\n", T);
}

int main()
{
	int n;
	printf("Array size: ");
	scanf("%d", &n);
	double* f = new double[n];
	complex* a = new complex[n];
	if (a == NULL || f == NULL) {
		printf("\nERROR\n");
		system("Pause");
		return 1;
	}
	FillRand(f, n);
	Output(f, n);
	DFT(f, a, n);
	Output(a, n);
	SFFT(f, a, n);
	Output(a, n);
	FFT(f, a, n);
	Output(a, n);
	system("Pause");
	return 0;
}
