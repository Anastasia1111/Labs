#include <stdlib.h>
#include <stdio.h>
#include <string>

#define MSIZE 256

using namespace std;

struct alph
{
	unsigned char a;
	double p;
	double q;
} *A = NULL;

double *L, *H, *R;

void creating ();
void p_a_calc(string mess, int n);
void ariph (string mess, int n);

int main (void)
{
	string mess = "qweryuio";
	creating ();
	void p_a_calc(string mess, int n);
	
	
	return 0;
}

void p_a_calc(string mess, int n)
{
	int i = 0, j = 0;
	
	for (i = 0; i < n; ++i)
	{
		j = mess[i];
		if(j < 0)
			j += 256;
		A[j].p = A[j].p + 1.0;
	}
	
	for (i = 0; i < MSIZE; ++i)
	{
		A[i].p = A[i].p / n;
	}
	for (i = 1; i < MSIZE; ++i)
	{
		A[i].q = A[i-1].q + A[i-1].p;
	}
}

void creating ()
{
	A = new alph[MSIZE];
	L = new double [MSIZE];
	H = new double [MSIZE];
	R = new double [MSIZE];
	
	for (int i = 0; i < MSIZE; ++i)
	{
		A[i].a = i;
		A[i].p = 0.0;
		A[i].q = 0.0;
		L[i] = 0.0;
		H[i] = 0.0;
		R[i] = 0.0;
	}
	
}

void ariph (string mess, int n)
{
	
}
