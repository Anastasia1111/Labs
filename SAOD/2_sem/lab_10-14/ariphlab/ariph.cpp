#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <locale.h>
#include <climits>

#define MSIZE 256

using namespace std;

struct alph
{
	unsigned char a;
	double p;
	double q;
} *A = NULL;

unsigned int r = UINT_MAX;

void creating();
void printalph();
void p_a_calc(string mess, int n);
int ariph (string mess, int n, FILE *RCf);
int decode (string mess, FILE *RCf, int length);

int main()
{
	string mess = "cout << mess << endl << mess.length() << endl;\n\
	\n\
	\n\
	for (i = 0; i < size; ++i)\n\
	{\n\
		A[i].a = i;\n\
		A[i].p = 0.0;\n\
		codewords[i] = \"\";\n\
	}\n\
	\n\
	p_a_calc(mess, mess.length());\n\
	for (i = 0; i < size; ++i)\n\
	{\n\
		p1[i] = A[i].p;\n\
	}\n\
	i = 0;\n\
	while (p1[i] != 0.0)\n\
		++i;\n\
	int n = i;\n\
	Huffman (n);\n\
	\n\
	cout << \"Coding (Huffman):\" << endl;\n\
	printalph();\n\
	\n\
	system(\"pause\");\n\
	double h = 0, ml = 0;\n\
	for(i = 0; i < size; ++i)\n\
	{\n\
		if(A[i].p > 0)\n\
		{\n\
			h += -1 * A[i].p * log2(A[i].p);\n\
			ml += codewords[i].length() * A[i].p;\n\
		}\n\
	}\n\
	\n\
	printf(\"\nEntropia: %1.4f, Mid length: %1.4f\n\",h,ml);\n\
	system(\"pause\");\n\
	\n\
	encodeInFile(mess,n);\n\
	system(\"PAUSE\");\n\
	decode();\n\
	system(\"pause\");\n\
	delete A;\n\
	delete p1;\n\
	delete codewords;\n\
	return 0;\n\
}\n\
\n\
\n\
void p_a_calc(string mess, int n)\n\
{\n\
	int i = 0, j = 0;\n\
	\n\
	for (i = 0; i < n; ++i)\n\
	{\n\
		j = mess[i];\n\
		if(j < 0)\n\
			j += 256;\n\
		A[j].p = A[j].p + 1.0;\n\
	}\n\
	\n\
	for (i = 0; i < size; ++i)\n\
	{\n\
		A[i].p = A[i].p / n;\n\
	}\n\
	sort(A, A + size, compar);\n\
	reverse(A, A+size);\n\
}\n\
\n\
void Huffman (int n)\n\
{\n\
	int j;\n\
	double q;\n\
	if (n == 2)\n\
	{\n\
		codewords[n-2] = \"0\";\n\
		codewords[n-1] = \"1\";\n\
	} else {\n\
		q = p1[n-2] + p1[n-1];\n\
		j = Up (n, q);\n\
		Huffman (n-1);\n\
		Down (n, j);\n\
	}\n\
}";
	int len = mess.length();
	FILE *RCf = fopen("ariphtext.dat", "wb+");
	
	creating ();
	p_a_calc(mess, len);
	printalph();
	system("pause");
	
	int messlen = ariph (mess, len, RCf);
	printf("%i symbols encoded", messlen);
	fclose(RCf);
	system("pause");
	RCf = fopen("ariphtext.dat", "rb+");
	string decodemess = "";
	messlen = decode (decodemess, RCf, len);
	system("pause");
	return 0;
}

void creating ()
{
	A = new alph[MSIZE];
	
	for (int i = 0; i < MSIZE; ++i)
	{
		A[i].a = i;
		A[i].q = 0;
		A[i].p = 0;
	}
}

void p_a_calc(string mess, int n)
{
	int i = 0;
	unsigned char j = 0;
	
	for(i = 0; i < n; ++i){
		j = mess[i];
		++A[j].p;
	}
	
	for (i = 0; i < MSIZE; ++i)
	{
		A[i].p /= n;
	}
	A[0].q = A[0].p;
	for (i = 1; i < MSIZE; ++i)
	{
		A[i].q = A[i-1].q + A[i].p;
	}
}

void printalph()
{
	for (int i = 0; i < MSIZE; ++i)
	{
		if(A[i].p != 0)
		{
			printf("%4i. [%c]:  prob: %1.5f ", i, A[i].a, A[i].p);
			printf("  %1.5f\n", A[i].q);
		}
	}
}

int ariph (string mess, int n, FILE *RCf)
{
	unsigned int h = UINT_MAX;
	unsigned int hpr = UINT_MAX;
	unsigned int l = 0;
	unsigned int lpr = 0;
	int k = 0;
	
	unsigned char C;
	int m = 0;
	int j = 0;
	int i;
	for(i = 0; i < n; ++i){
		C = mess[i];
		printf("%c", C);
		++k;
		for (j = 0; j < MSIZE; j++)
		{
			if(C == A[j].a)
			{
				m = j;
				break;
			}
		}
		
		if(m)
			l = lpr + (unsigned int)(r * A[m-1].q);
		h = lpr + (unsigned int)(r * A[m].q);
		lpr = l;
		hpr = h;
		if((l^h) <= 16777215) // last byte is equal
		{
			char c = (char)(l >> 24);
			fputc((int)c, RCf);
			l <<= 8;// delete last byte
			h <<= 8;
			h += 255;
		}
		r = h - l;
	}
	
	char last;
	for(i = 24; i >= 0; i -= 8)
	{
		last = (char) ((l + r/2) >> i);
		fputc((int)last, RCf);
	}
	return k;
}

int decode (string mess, FILE *RCf, int length)
{
	unsigned int h = UINT_MAX;
	unsigned int hpr = UINT_MAX;
	unsigned int l = 0;
	unsigned int lpr = 0;
	unsigned char c;
	unsigned int number = 0;
	string codemess = "";
	r = UINT_MAX;
	int i, j;
	int codecount = 0;
	while(!feof(RCf))
	{
		c = fgetc(RCf);
		codemess = codemess + (char)c;
	}
	for(i = 0; i < 4; ++i)
	{
		number <<= 8;
		if(codecount < codemess.length())
		{
			number += (unsigned char) codemess[codecount];
			++codecount;
		}
	}	
	for(i = 0; i < length; ++i)
	{
		for(j = 0; j < MSIZE; ++j)
		{
			if(j)
				l = lpr + (unsigned int)(r * A[j-1].q);
			h = lpr + (unsigned int)(r * A[j].q);
			if((l <= number) && (number < h))
			{
				mess = mess + (char) (A[j].a);
				break;	
			}
		}
		if((l^h) <= 16777215) // last byte is equal
		{
			l <<= 8;// delete last byte
			h <<= 8;
			h += 255;
			number <<= 8;
			if(codecount < codemess.length())
			{
				number += (unsigned char) codemess[codecount];
				++codecount;
			}
		}
		r = h - l;
		lpr = l;
		hpr = h;
	}
	cout << mess << endl;
}
