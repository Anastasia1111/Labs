#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include "complex.h"

#define PI 3.14159265359

void conv(Complex *a, Complex *b, Complex *c, int n);
void DFTconv(Complex *a, Complex *b, Complex *c, int n);
void SFFTconv(Complex *a, Complex *b, Complex *c, int n);
void FFTconv(Complex *a, Complex *b, Complex *c, int n);

void DFT(Complex* f, Complex* a, int n);
void DFTInv(Complex *a, Complex *f, int n);

void SFFT(Complex* f, Complex* a, int n);
void SFFTInv(Complex* f, Complex* a, int n);

void FFT(Complex* f, Complex* a, int n);
void FFTInv(Complex* f, Complex* a, int n);

void random(Complex *a, int n);
double fRand(double fMin, double fMax);
void print_arr(Complex *a, int n);

int T;


int main(int argc, char const *argv[])
{
	srand(time(0));

	int n;
	n = 32;
	printf("n = %i\n", n);
	Complex *a = new Complex [n];
	Complex *b = new Complex [n];
	Complex *c = new Complex [2*n];
	int Tc[4];
	random(a, n);
	random(b, n);

	printf("arr a:\n");
	print_arr(a,n);
	printf("arr b:\n");
	print_arr(b,n);


/*	T = 0;
	DFT(a, c, n);
	printf("DFT:\n");
	printf("T = %d\n\n", T);
	print_arr(c, n);
	T = 0;
	DFTInv(c, b, n);
	printf("DFTInv:\n");
	printf("T = %d\n\n", T);
	print_arr(b, n);
*/	
	/*T = 0;
	SFFT(a, c, n);
	printf("SFFT:\n");
	printf("T = %d\n\n", T);
	print_arr(c, n);
	T = 0;
	SFFTInv(c, b, n);
	printf("SFFTInv:\n");
	printf("T = %d\n\n", T);
	print_arr(b, n);
	
	T = 0;
	FFT(a, c, n);
	printf("FFT:\n");
	printf("T = %d\n\n", T);
	print_arr(c, n);
	T = 0;
	FFTInv(c, b, n);
	printf("FFTInv:\n");
	printf("T = %d\n\n", T);
	print_arr(b, n);*/

	T = 0;
	conv(a, b, c, n);
	printf("Standart conv:\n");
	print_arr(c, 2*n-1);
	Tc[0] = T;
	puts("");

	T = 0;
	DFTconv(a, b, c, n);
	printf("DFT conv:\n");
	print_arr(c, 2*n);
	Tc[1] = T;
	puts("");

	T = 0;
	SFFTconv(a, b, c, n);
	printf("SFFT conv:\n");
	print_arr(c, 2*n);
	Tc[2] = T;
	puts("");

	T = 0;
	FFTconv(a, b, c, n);
	printf("FFT conv:\n");
	print_arr(c, 2*n);
	Tc[3] = T;
	puts("\n");

	printf("Labour:\n");
	printf("T(standard conv) = %i\n", Tc[0]);
	printf("T(DFT conv) = %i\n", Tc[1]);
	printf("T(SFFT conv) = %i\n", Tc[2]);
	printf("T(FFT conv) = %i\n", Tc[3]);

	system("Pause");
	return 0;
}

void conv(Complex *a, Complex *b, Complex *c, int n)
{
	int i, j;
	T = 0;
	printf("n = %i\n", n);
	for(i = 0; i < 2*n-1; ++i)
		c[i] = 0.0;

	for(i = 0; i < n; ++i)
	{
		for(j = 0; j <= i; ++j)
		{
			c[i] += a[j]*b[i-j];
			T++; 
			if(i != 2*n-i-2)
			{
				c[2*n-i-2] += a[n-1-j]*b[n-1-i+j];
				T++; 
			}
			
		}
	}
}

void DFTconv(Complex *a, Complex *b, Complex *c, int n){
	int i;
	Complex *long_a = new Complex [2*n];
	Complex *long_b = new Complex [2*n];
	for(i = 0; i < 2*n; ++i)
		c[i] = 0;
	for(i = 0; i < n; ++i)
	{
		long_a[i] = a[i];
		long_b[i] = b[i];
	}
	for(i = n; i < 2*n; ++i)
	{
		long_a[i] = 0.0;
		long_b[i] = 0.0;
	}

	Complex *fa = new Complex [2*n];
	Complex *fb = new Complex [2*n];
	Complex *fc = new Complex [2*n];
	DFT (long_a, fa, 2*n);
	DFT (long_b, fb, 2*n);
	for(i = 0; i < 2*n; ++i)
	{
		fc[i] = fa[i] * fb[i] * 2.0 * n; // now here should be an Fourier of convolution
		T ++;
	}
	DFTInv (fc, c, 2*n);
}

void SFFTconv(Complex *a, Complex *b, Complex *c, int n) 
{
	int i;
	Complex *long_a = new Complex [2*n];
	Complex *long_b = new Complex [2*n];
	for(int i = 0; i < 2*n; ++i)
		c[i] = 0;
	for(i = 0; i < n; ++i)
	{
		long_a[i] = a[i];
		long_b[i] = b[i];
	}
	for(i = n; i < 2*n; ++i)
	{
		long_a[i] = 0.0;
		long_b[i] = 0.0;
	}

	Complex *abuf = new Complex [2*n];
	Complex *bbuf = new Complex [2*n];
	Complex *cbuf = new Complex [2*n];
	SFFT (long_a, abuf, 2*n);
	SFFT (long_b, bbuf, 2*n);
	for(i = 0; i < 2*n; ++i)
	{
		cbuf[i] = abuf[i] * bbuf[i] * 2.0 * n; // now here should be an Fourier of convolution
		T ++;
	}
	SFFTInv (cbuf, c, 2*n);
}

void FFTconv(Complex *a, Complex *b, Complex *c, int n) 
{
	int i;
	int nr = 2;
	while(nr < n)
		nr <<= 1;
	Complex *long_a = new Complex [2*nr];
	Complex *long_b = new Complex [2*nr];
	for(int i = 0; i < 2*n; ++i)
		c[i] = 0;
	for(i = 0; i < n; ++i)
	{
		long_a[i] = a[i];
		long_b[i] = b[i];
	}
	for(i = n; i < 2*nr; ++i)
	{
		long_a[i] = 0.0;
		long_b[i] = 0.0;
	}

	Complex *abuf = new Complex [2*nr];
	Complex *bbuf = new Complex [2*nr];
	Complex *cbuf = new Complex [2*nr];
	Complex *cres = new Complex [2*nr];
	FFT (long_a, abuf, 2*nr);
	FFT (long_b, bbuf, 2*nr);

	for(i = 0; i < 2*nr; ++i)
	{
		cbuf[i] = abuf[i] * bbuf[i] * 2.0 * nr; // now here should be an Fourier of convolution
		T ++;
	}
	FFTInv (cbuf, cres, 2*n);
	for(i = 0; i < 2*n; ++i)
	{
		c[i] = cres[i];
	}
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
			a[k] = a[k] + f[j] * buf;
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
			f[k] = f[k] + (buf * a[j]);
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
				a1[k1][j2] = a1[k1][j2] + exp * f[j2 + p2 * j1];
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
				a2[k1][k2] = a2[k1][k2] + exp * a1[k1][j2];
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
				f1[k1][j2] = f1[k1][j2] + exp * a[j2 + p2 * j1];
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
				f2[k1][k2] = f2[k1][k2] + exp * f1[k1][j2];
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

void FFT(Complex *f, Complex *a, int n)
{
    int r = (int) log2(n);
    Complex **As = new Complex *[r + 1];
    for(int i = 0; i < r+1; ++i)
        As[i] = new Complex[n];

    Complex exp;

    for (int k = 0; k < n; ++k)
        As[0][k] = f[k];

    for (int s = 0; s < r; ++s)
    {
        for (int k = 0; k < n; ++k) 
        {
            As[s + 1][k] = As[s][(k & ~(1 << (r - s - 1)))];

            int k_sum = 0;
            for (int l = 0; l <= s; ++l)
                k_sum += ((k << l) & (1 << (r - 1))) >> (r - 1 - l);
            
            exp.set(cos(-1.0*PI*k_sum/(1 << s)), sin(-1.0*PI*k_sum/(1 << s)));
            int new_k = (k | (1 << (r - s - 1)));
            As[s + 1][k] = As[s + 1][k] + As[s][new_k] * exp;
            T += 4;
            As[s + 1][k] = As[s + 1][k] * 0.5;
        }
    }
    for (int k = 0; k < n; ++k)
    {
        int end = 0;
        for (int l = 0; l < r; ++l)
        	end = (end << 1) + ((k >> l) & 1);
        a[k] = As[r][end];
    }
}

void FFTInv(Complex *f, Complex *a, int n)
{
    int r = (int) log2(n);
    Complex **As = new Complex *[r + 1];
    for(int i = 0; i < r+1; ++i)
        As[i] = new Complex[n];

    Complex exp;

    for (int k = 0; k < n; ++k)
        As[0][k] = f[k];

    for (int s = 0; s < r; ++s)
    {
        for (int k = 0; k < n; ++k)
        {
            As[s + 1][k] = As[s][(k & ~(1 << (r - s - 1)))];

            int k_sum = 0;
            for (int l = 0; l <= s; ++l)
            {
                k_sum += ((k << l) & (1 << (r - 1))) >> (r - 1 - l);
            }
            
            exp.set(cos(1.0*PI*k_sum/(1 << s)), sin(1.0*PI*k_sum/(1 << s)));
            int new_k = (k | (1 << (r - s - 1)));
            As[s + 1][k] = As[s + 1][k] + As[s][new_k] * exp;
            T += 4;
        }
    }
    for (int k = 0; k < n; ++k)
    {
        int end = 0;
        for (int l = 0; l < r; ++l)
        	end = (end << 1) + ((k >> l) & 1);
        a[k] = As[r][end];
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
		printf("%i. ", i);
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
