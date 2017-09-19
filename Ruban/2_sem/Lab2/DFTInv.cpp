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


void DFTInv (complex *a, complex *f, int n);
void SFFTInv (complex* a, complex* f, int n);
void FFTInv (complex* a, complex* f, int n);
void FillRand(complex* a, int n);
complex AsInv(complex* a, int* k, int s, int jsum, int add);

//Isn't requred for integration
void Output(complex* a, int n);
double fRand(double fMin, double fMax);

int main()
{
	int n;
	printf("Array size: ");
	scanf("%d", &n);
	complex* f = new complex[n];
	complex* a = new complex[n];
	if (a == NULL || f == NULL) {
		printf("\nERROR\n");
		system("Pause");
		return 1;
	}
	FillComplexRand(a, n);
	Output(a, n);
	printf("(0 should be here, its just a print)\n");
	DFTInv(a, f, n);
	Output(f, n);
	SFFTInv(a, f, n);
	Output(f, n);
	FFTInv(a, f, n);
	Output(f, n);
	system("Pause");
	return 0;
}

void DFTInv (complex *a, complex *f, int n)
{
	T = 0;
	complex buf;
	for(int k=0; k<n; ++k)
	{
		f[k].re = 0;
		f[k].im = 0;
		for(int j=0; j<n; ++j)
		{
			buf.re = cos(2.0 * k * j * PI / n);
			buf.im = sin(2.0 * k * j * PI / n);
			f[k].re += buf.re*a[j].re - buf.im*a[j].im;
			f[k].im += buf.re*a[j].im + buf.im*a[j].re;
			++T;
		}
	}
}

void SFFTInv(complex* a, complex* f, int n)
{
	T = 0;
	complex buf;
	int p1, p2;
	p1 = (int)sqrt(n);
	while (n % p1)
		--p1;
	p2 = n/p1;

	for(int k=0; k<n; ++k)
	{
		int k1 = k % p1,
			k2 = k / p1;
		f[k].re = 0;
		f[k].im = 0;
		for(int j2=0; j2<p2; ++j2)
		{
			complex f1;
			f1.re = 0;
			f1.im = 0;
			for(int j1=0; j1<p1; ++j1)
			{
				buf.re = cos(2.0 * k1 * j1 * PI / p1);
				buf.im = sin(2.0 * k1 * j1 * PI / p1);
				f1.re +=  buf.re * a[j2 + p2 * j1].re - buf.im * a[j2 + p2 * j1].im;
				f1.im +=  buf.re * a[j2 + p2 * j1].im + buf.im * a[j2 + p2 * j1].re;
			}
			complex exp;
			exp.re = cos(2.0 * (k1 + p1 * k2) * j2 * PI / (p1 * p2));
			exp.im = sin(2.0 * (k1 + p1 * k2) * j2 * PI / (p1 * p2));
			f[k].re += f1.re * exp.re - f1.im * exp.im;
			f[k].im += f1.re * exp.im + f1.im * exp.re;
		}
	}
	T = n * (p1 + p2);
}

void FFTInv(complex* a, complex* f, int n)
{
	T = 0;
	
	int r = (int)log2(n);
	int* k = new int[r];
	for(int km=0; km<n; ++km)
	{
		f[km].re = 0;
		f[km].im = 0;
		int kt = km;
		for(int l=0; l<r; ++l)
		{
			k[l] = kt % 2;
			kt /= 2;
		}
		f[km] = AsInv(a, k, r, 0, 1);
	}
	T = n * r;
}

complex AsInv(complex* a, int* k, int s, int jsum, int add)
{
	complex res;
	complex exp;
	double pow;
	if (s == 0)
	{
		res.re = a[jsum].re;
		res.im = a[jsum].im;
	} else {
		res = AsInv(a, k, s - 1, jsum, add * 2);
		complex tmp = AsInv(a, k, s - 1, jsum + add, add * 2);
		complex exp;
		double power = 0;
		for (int l=0; l<s; ++l)
			power += k[l] * (2 << l);
		power *= 2.0 * PI /(2 << s);
		exp.re = cos(power);
		exp.im = sin(power);
		res.re += tmp.re * exp.re - tmp.im * exp.im;
		res.im += tmp.re * exp.im + tmp.im * exp.re;
	}
	return res;
}
void FillRand(complex* a, int n)
{
	srand(time(0));
	for (int i=0; i<n; ++i)
	{
		a[i].re = fRand(-1.0 * n, 1.0 * n);
		a[i].im = fRand(-1.0 * n, 1.0 * n);
	}

}

void Output(complex* a, int n)
{
	printf("\nArray:\n");
	for (int i=0; i<n; ++i)
		printf("(%.3f + %.3fi)\n", a[i].re, a[i].im);
	printf("T = %d*C\n", T);
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


