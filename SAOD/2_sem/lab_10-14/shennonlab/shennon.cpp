#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define size 94

void InsertSort(double* p, char *a)
{
	int i, j;
	double t1;
	char t2;
	for (i = 1; i < size; ++i) {
		t1 = p[i]; 
		t2 = a[i];
		for (j = i - 1; (j >= 0) && (t1 >= p[j]); j--)
		{
			p[j+1] = p[j];
			a[j+1] = a[j];
		}
		p[j+1] = t1;
		a[j+1] = t2;
	}
}

void p_a_calc(char *mess, int n, double *&p, char *a)
{
	int i = 0, j = 0;
	
	for (i = 0; i < size; ++i)
	{
		p[i] = 0.0;
		a[i] = i + 32;
	}
	
	for (i = 0; i < n; ++i)
	{
		j = mess[i] - 32;
		p[j] = p[j] + 1.0;
	}
	
	for (i = 0; i < size; ++i)
	{
		p[i] = p[i] / n;
	}
}

void q_l_calc(double *p, double *q, int *l)
{
	int i = 0;
	q[0] = 0;
	p[0] != 0.0 ? l[0] = (int)(-1 * log2(p[i]) + 1) : l[0] = 0;
	for (i = 1; i < size; ++i)
	{
		q[i] = q[i-1] + p[i-1];
		p[i] != 0.0 ? l[i] = (int)(-1 * log2(p[i]) + 1) : l[i] = 0;
	}
}

void codewords_calc(char **codewords, int *l, double *q)
{
	int i, j;
	for(i = 0; i < size; ++i)
	{
		codewords[i] = new char [l[i]];
		for(j = 0; j < l[i]; ++j)
		{
			q[i] = q[i] * 2;
			codewords[i][j] = (char)(q[i] + 48);
			if(q[i] > 1) q[i] -= 1; 
		}
	}
}


main()
{
	int i, j;
	char *mess = "qwertyuiop[];dzglknj[erausojn.g,nx'jhothsn'k;lsh[APUSETH[0SBSB;BW;MMPMEE*(&%*$^%$@#asdfghjk";
	double *p = new double [size];
	char *a = new char [size];
	double *q = new double [size];
	int *l = new int [size];
	
	char **codewords = new char *[size];
	
	p_a_calc(mess, strlen(mess), p, a);
	InsertSort(p, a);
	q_l_calc(p, q, l);
	codewords_calc(codewords, l, q);

	
	for (i = 0; i < size; ++i)
	{
		printf("%3i. %c = %f - %i - ", i+1, a[i], p[i], l[i]);
		for(j = 0; j < l[i]; ++j)
			printf("%c", codewords[i][j]);
		puts("");
	}
	
	double h = 0, ml = 0;
	for(i = 1; i < 94; ++i)
	{
		if(p[i] > 0)
		{
			h += -1*p[i] * log2(p[i]);
			ml += l[i] * p[i-1];
		}
	}
	
	printf("\nEntropia: %1.4f, Mid length: %1.4f",h,ml);
	
	system("pause");
}
