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
} *A = NULL;
double *p1 = NULL;

string *codewords = NULL;

void Huffman (int n);
int Up (int n, double q);
int Down (int n, int j);
void p_a_calc(string mess, int n);
void InsertSort();
void printalph();
bool compar(alph a, alph b);

//***********************************************

main()
{
	int i;
	A = new alph[size];
	p1 = new double [size];
	codewords = new string[size];
	string mess = "sjhg 5u 3q8twykghjs oq34y93ogesjghl erjkh qp98tw ghpo dfh";
	
	for (i = 0; i < size; ++i)
	{
		A[i].a = i;
		A[i].p = 0.0;
		codewords[i] = "";
	}
	
	p_a_calc(mess, mess.length());
	for (i = 0; i < size; ++i)
	{
		p1[i] = A[i].p;
	}
	i = 0;
	while (p1[i])
		++i;
	Huffman (i);
	
	cout << "Coding (Huffman):" << endl;
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
	delete p1;
	delete codewords;
	return 0;
}

//***************************************************\\

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

/*void InsertSort()
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
}*/

void Huffman (int n)
{
	int j;
	double q;
	if (n == 2)
	{
		codewords[n-2] = "0";
		codewords[n-1] = "1";
	} else {
		q = p1[n-2] + p1[n-1];
		j = Up (n, q);
		Huffman (n-1);
		Down (n, j);
	}
}

int Up (int n, double q)
{
	int j;
	int i;
	for (i = n-2; i > 0; --i)
	{
		if(p1[i-1] <= q)
			p1[i] = p1[i-1];
		else 
			j = i;
	}
	if (!i)
		j = 0;
	p1[j] = q;
	return j;
}

int Down (int n, int j)
{
	string s = codewords[j];
	for (int i = j; i < (n - 2); ++i)
	{
		codewords[i] = codewords[i+1];
	}
	codewords[n-2].clear();
	codewords[n-1].clear();
	codewords[n-2] = s + "0";
	codewords[n-1] = s + "1";
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
