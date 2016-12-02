#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <math.h>

#define size 255

using namespace std;

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

void p_a_calc(string mess, int n, double *&p, char *a)
{
	int i = 0, j = 0;
	
	for (i = 0; i < n; ++i)
	{
		j = mess[i];
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

void codewords_calc(string *codewords, int *l, double *q)
{
	int i, j;
	for(i = 0; i < size; ++i)
	{
		for(j = 0; j < l[i]; ++j)
		{
			q[i] = q[i] * 2;
			codewords[i] += (char)(q[i] + 48);
			if(q[i] > 1) q[i] -= 1; 
		}
	}
}

void FileRead (string &m, const char *filename)
{
	FILE *pf;
	pf = fopen(filename, "rb+");
	char buff[] = {0,0};
	do
	{
		fgets(buff, 2, pf);
		m += buff[0];
	} while(!feof(pf));
	fclose(pf);
}

void CodeMess (string &mess, string &codemess, char *a, string *codewords)
{
	codemess = "";
	
	char j;
	int k;
	int bit_count = 0;
	char buffcode;
	
	for (int i = 0; i < mess.length(); ++i)
	{
		j = mess[i];
		printf("%c", j);
		k = 0;
		while(j != a[k])
		{
			++k;
		}
		//free j;
		
		for(int j = 0; j < codewords[k].length(); ++j)
		{
			if(bit_count == 8)
			{
				codemess = codemess + buffcode;
				buffcode = 0;
				bit_count = 0;
			}
			if(codewords[k][j] == '1')
			{
				buffcode += 1;
			}
			buffcode <<= 1;
			++bit_count;
		}
	}
	while(bit_count != 8)
	{
		buffcode <<= 1;
		++bit_count;
	}
}


void PrintInFile (string &m, const char *filename)
{
	FILE *pf;
	pf = fopen(filename, "wb+");
	char buff[] = {0,0};
	int i = 0;
	do
	{
		buff[0] = m[i];
		fputc(buff[0], pf);
		i++;
	} while(i < m.length());
	fclose(pf);
}

void Decoder(char *a, double *p, string *codewords, const char *filename)
{
	FILE *pF, *pDF;
	pF = fopen(filename, "rb");
	pDF = fopen("decoding_results.dat","wb");
	int j;
	if (pF != NULL)
	{
		int CWNum = 0;
		while(p[CWNum])
		{
			CWNum++;
		}
		unsigned char buf = 0;
		int bit_count = 0;
		unsigned char bit = 0;
		string str_bit = "";
		int i = 0;
		do
		{
  			buf = fgetc(pF);
  			for(bit_count = 0; bit_count != 8; bit_count++){
				bit = buf << bit_count;
				bit >>= 7;
				if (bit){
					str_bit += '1';
				} else {
					str_bit += '0';
				}
				cout << str_bit<< endl;
				for(j = 0; j < CWNum; j++)
				{
					if (!str_bit.compare(codewords[j]))
					{
						fputc((int)a[j], pDF);
						str_bit.clear();
						str_bit = "";
					}
				}
			}
			i++;
		}while(!feof(pF) && i < 10);
	}
}

main()
{
	int i, j;
	string mess = "";
	string codemess = "";
	double *p = new double [size];
	char *a = new char [size];
	double *q = new double [size];
	int *l = new int [size];
	
	string *codewords = new string[size];
	
	for (i = 0; i < size; ++i)
	{
		p[i] = 0.0;
		a[i] = i;
	}
	
	FileRead(mess, "engfile.dat");
	cout << mess << endl;
	p_a_calc(mess, mess.length(), p, a);
	InsertSort(p, a);
	q_l_calc(p, q, l);
	codewords_calc(codewords, l, q);
	for (i = 0; i < size; ++i)
	{
		printf("%3i. %c = %f - %i - ", i+1, a[i], p[i], l[i]);
		cout << codewords[i] << endl;
	}
	cout << mess.length() << endl;
	CodeMess(mess, codemess, a, codewords);
	cout << codemess << endl;
	cout << codemess.length() << endl;
	PrintInFile(codemess, "codefile.dat");
	mess.clear();
	codemess.clear();
	system("pause");
	Decoder(a, p, codewords, "codefile.dat");
	double h = 0, ml = 0;
	for(i = 0; i < size; ++i)
	{
		if(p[i] > 0)
		{
			h += -1 * p[i] * log2(p[i]);
			ml += l[i] * p[i];
		}
	}
	
	printf("\nEntropia: %1.4f, Mid length: %1.4f",h,ml);
	
	delete p;
	delete a;
	delete q;
	delete l;
	delete codewords;	
	
	system("pause");
}
