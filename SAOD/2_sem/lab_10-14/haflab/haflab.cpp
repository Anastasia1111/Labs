#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#define size 94

using namespace std;

char *a = NULL;
double *p = NULL;
double *p1 = NULL;

string *codewords = NULL;

void Huffman (int n);
int Up (int n, double q);
int Down (int n, int j);
void p_a_calc(string mess, int n);
void InsertSort();
void printalph();

//***********************************************

main()
{
	int i;
	a = new char[size];
	p = new double [size];
	p1 = new double [size];
	codewords = new string[size];
	string mess = "dwabsdfghdgh iij y3n5987wiughgiu2tgi tw gbk fj gdlk";
	
	for (i = 0; i < size; ++i)
	{
		a[i] = i + 32;
		p[i] = 0.0;
		codewords[i] = "";
	}
	
	p_a_calc(mess, mess.length());
	for (i = 0; i < size; ++i)
	{
		p1[i] = p[i];
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
		if(p[i] > 0)
		{
			h += -1 * p[i] * log2(p[i]);
			ml += codewords[i].length() * p[i];
		}
	}
	
	printf("\nEntropia: %1.4f, Mid length: %1.4f\n",h,ml);
	system("pause");
	delete a;
	delete p;
	delete codewords;
	return 0;
}

//***************************************************\\

void p_a_calc(string mess, int n)
{
	int i = 0, j = 0;
	
	for (i = 0; i < n; ++i)
	{
		j = mess[i] - 32;
		p[j] = p[j] + 1.0;
	}
	
	for (i = 0; i < size; ++i)
	{
		p[i] = p[i] / n;
	}
	InsertSort();
}

void InsertSort()
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
		printf("hey! %i\n", n);
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
		printf("%4i. %c:  prob: %1.5f ", i, a[i], p[i]);
		cout << codewords[i] << " Length:" << codewords[i].length() << endl;
	}
}
