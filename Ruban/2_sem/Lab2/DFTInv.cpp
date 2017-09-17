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
void FFTInv ();
void FillComplexRand(complex* a, int n);

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
	/*SFFT(f, a, n);
	Output(a, n);
	FFT(f, a, n);
	Output(a, n);*/
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
		f[k].re /= n;
		f[k].im /= n;
	}
}

void SFFTInv(complex* a, complex* f, int n)
{

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

void FillComplexRand(complex* a, int n)
{
	srand(time(0));
	for (int i=0; i<n; ++i)
	{
		a[i].re = fRand(-1.0 * n, 1.0 * n);
		a[i].im = fRand(-1.0 * n, 1.0 * n);
	}

}
