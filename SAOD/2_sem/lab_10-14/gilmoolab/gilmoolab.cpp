#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#define size 256

using namespace std;

struct alph
{
	char a;
	double p;
	double q;
	int l;
} *A = NULL;

string *codewords = NULL;

void p_a_calc(string mess, int n);
void q_calc();
void codewords_calc();
void printalph();
bool compar(alph a, alph b);

//*************************************************

main()
{
	int i;
	A = new alph[size];
	codewords = new string[size];
	string mess = "qwertyuiasdfghjkQWERTYUIASDFGHJK214356789";
	
	for (i = 0; i < size; ++i)
	{
		A[i].a = i;
		A[i].p = 0.0;
		codewords[i] = "";
	}
	
	p_a_calc(mess, mess.length());
	q_calc();
	codewords_calc();
	printalph();
	system("pause");
	
	double h = 0, ml = 0;
	for(i = 0; i < size; ++i)
	{
		if(A[i].p > 0)
		{
			h += -1 * A[i].p * log2(A[i].p);
			ml += codewords[i].length() * A[i].p;
		}
	}
	
	printf("\nEntropia: %1.4f, Mid length: %1.4f\n",h,ml);
	system("pause");
	
	delete A;
	delete codewords;
	return 0;
}

//**************************************************

void p_a_calc(string mess, int n)
{
	int i = 0, j = 0;
	
	for (i = 0; i < n; ++i)
	{
		j = mess[i];
		A[j].p = A[j].p + 1.0;
	}
	
	for (i = 0; i < size; ++i)
	{
		A[i].p = A[i].p / n;
	}
	sort(A, A + size, compar);
	reverse(A, A+size);
}

void q_calc()
{
	int i = 0;
	A[0].q = 0;
	
	A[0].p != 0.0 ? A[0].l = (int)(-1 * log2(A[0].p) + 1) : A[0].l = 0;
	for (i = 1; i < size; ++i)
	{
		A[i].q = A[i-1].q + A[i-1].p;
		A[i].p != 0.0 ? A[i].l = (int)(-1 * log2(A[i].p) + 1) : A[i].l = 0;
	}
	for (i = 0; i < size; ++i)
	{
		A[i].q = A[i].q + A[i].p / 2;
	}
}

void codewords_calc()
{
	int i, j;
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < A[i].l; ++j)
		{
			A[i].q = A[i].q * 2;
			codewords[i] += (char)(A[i].q + 48);
			if(A[i].q > 1) A[i].q -= 1; 
		}
	}
}

void printalph()
{
	for (int i = 0; i < size; ++i)
	{
		printf("%4i. %c:  prob: %1.5f ", i, A[i].a, A[i].p);
		cout << codewords[i] << " Length:" << codewords[i].length() << endl;
	}
}

bool compar(alph a, alph b)
{
	return a.p < b.p;
};
