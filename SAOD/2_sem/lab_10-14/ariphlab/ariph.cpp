#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <locale.h>

#define MSIZE 256

using namespace std;

struct alph
{
	unsigned char a;
	int pnumer;
	int pdenom;
	int qnumer;
	int qdenom;
} *A = NULL;

int Rnumer;
int Rdenom;

char Read(FILE *rf);
void creating ();
void p_a_calc(string mess, int n);
void printalph();
int ariph (string mess, int n, int &fnum, int &fden);
void writeBinInFile (FILE *RCf, int numer, int denom, int unsize);
void readBinFromFile (FILE *rf, int &numer, int &denom);
void decalph (FILE *rf, int symnum);
void flNumSum(int &aNum, int &aDen, int &bNum, int &bDen, int &ResNum, int &ResDen);

int NOD(int a, int b)
{
    while (a && b)
        if (a >= b)
           a -= b;
        else
           b -= a;
    return a | b;
}
 
int NOK (int a, int b)
{
    return a * b / NOD (a, b);
}

void sokr(int &num, int &denom)
{
	enum prost {2, 3, 5, 7, 11, 13, 17, 19}
	for (prost i = 2; i < )
	while (!(denom%i)){
		num /= i;
		denom /= i;
	}
}

main()
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
	string codemess = "";
	FILE *RCf = fopen("ariphtext.dat", "wb+");
	int fnum, fden;
	
	creating ();
	p_a_calc(mess, len);
	printalph();
	system("pause");
	
	int messlen = ariph (mess, len, fnum, fden);
	printf("%i / %i (length: %i)", fnum, fden, messlen);
	system("pause");
	
	/*fseek(Pf, 0, SEEK_END);
	int unsize = ftell(Pf);
	writeBinInFile (RCf, fnum, fden, unsize);
	fclose (RCf);
	cout << "Writing in file..." << endl;
	system("pause");
	
	RCf = fopen("ariphtext.dat", "rb+");
	readBinFromFile(RCf, fnum, fden);
	decalph (RCf, messlen);
	
	fclose (Pf);
	fclose (RCf);*/
}

char Read(FILE *rf)
{
	if (rf != NULL && !feof(rf))
	{
		return fgetc(rf);
	}
	return 0;
}

void creating ()
{
	A = new alph[MSIZE];
	
	for (int i = 0; i < MSIZE; ++i)
	{
		A[i].a = i;
		A[i].pnumer = 0;
		A[i].pdenom = 0;
		A[i].qnumer = 0;
		A[i].qdenom = 0;
	}
}

void p_a_calc(string mess, int n)
{
	int i = 0;
	unsigned char j = 0;
	
	for(i = 0; i < n; ++i){
		j = mess[i];
		++A[j].pnumer;
	}
	
	for (i = 0; i < MSIZE; ++i)
	{
		A[i].pdenom = A[i].qdenom = n;
	}
	A[0].qnumer = A[0].pnumer;
	for (i = 1; i < MSIZE; ++i)
	{
		A[i].qnumer = A[i-1].qnumer + A[i].pnumer;
	}
}

void printalph()
{
	for (int i = 0; i < MSIZE; ++i)
	{
		if(A[i].pnumer != 0)
		{
			printf("%4i. [%c]:  prob: %1.5f ", i, A[i].a, (double)A[i].pnumer / A[i].pdenom);
			cout << (double)A[i].qnumer / A[i].qdenom;
			printf("  (%i) (%i)\n", A[i].qnumer, A[i].qdenom);
		}
	}
}

int ariph (string mess, int n, int &fnum, int &fden)
{
	int lnum = 0;
	int lden = 1; // L = 0
	
	int hnum = 1;
	int hden = 1; // H = 1
	
	Rnumer = Rdenom = 1; // R = 1
	
	int i = 0;
	int j = 0;
	
	int m = 0;
	int mnum, mden, m1num, m1den;
	
	printf("\nRnumer = %i, Rdenom = %i \n\n", Rnumer, Rdenom);
	
	unsigned char C;
	int l = 0;
	for(l = 0; l < n; ++l){
		C = mess[l];
		++i;
		for (j = 0; j < MSIZE; j++)
		{
			if(C == A[j].a)
			{
				m = j;
				break;
			}
		}
		
		int nlnum = -1 * lnum;
		mnum = Rnumer * A[m].qnumer;
		mden = Rdenom * A[m].qdenom;
		m1num = Rnumer * A[m-1].qnumer;
		m1den = Rdenom * A[m-1].qdenom;
		flNumSum(lnum, lden, mnum, mden, hnum, hden); // h = l + r*q
		if (m)
			flNumSum(lnum, lden, m1num, m1den, lnum, lden); // l = l + r*q
		flNumSum(hnum, hden, nlnum, lden, Rnumer, Rdenom); // r = h - l
		printf("Lnumer = %i, Ldenom = %i \n", lnum, lden);
		printf("Hnumer = %i, Hdenom = %i \n", hnum, hden);
		printf("Rnumer = %i, Rdenom = %i \n\n", Rnumer, Rdenom);
	}
	flNumSum(lnum, lden, hnum, hden, fnum, fden);
	fden *= 2;
	return i;
}

void writeBinInFile (FILE *RCf, int numer, int denom, int unsize)
{
	printf("numer = %i, denom = %i\n", numer, denom);
	string binCode = "";
	int n = (int) (log2(Rdenom) - log2(Rnumer));
	cout << "aprox = " << n << endl;
	int i;
	char buf = 0;
	char bit_count = 0;
	for (i = 0; i < n; ++i)
	{
		numer = numer * 2;
		if (numer >= denom)
		{
			binCode = binCode + '1';
			numer -= denom;
		} else {
			binCode = binCode + '0';
		}
	}
	if (binCode[i-1] == '0')
	{
		do
		{
			numer = numer * 2;
			if (numer >= denom)
			{
				binCode = binCode + '1';
				numer -= denom;
			} else {
				binCode = binCode + '0';
			}
			++i;
		} while (binCode[i-1] != '1');
	}
	if (RCf != NULL)
	{
		for (int k = 0; k < binCode.length(); k++)
		{
			if (bit_count==8)
			{
				fputc((int)buf, RCf);
				buf = 0;
				bit_count = 0;
			}
			buf <<= 1;
			if(binCode[k]=='1')
			{
				buf++;
			}
			bit_count++;
		}
		if(bit_count!=0)
		{
			for(int j=bit_count; j<8; j++)
				buf<<=1;
			fputc((int)buf, RCf);
			buf = 0;
			bit_count = 0;
		}
	} else {
		puts("\nERROR! Something unexpected caused a plem! Encoding results wastn't created!\n");
		system("PAUSE");
		exit(1);
	}
	
	fseek(RCf, 0, SEEK_END);
	int fsize = ftell(RCf);
	
	cout << "size (virtual) of uncoded file: "<<unsize<<" bytes\nsize of ariphtext.dat: " << fsize << " bytes\n";
	cout << "compressing:" << (double)fsize/unsize * 100 << endl;
}

void flNumSum(int &aNum, int &aDen, int &bNum, int &bDen, int &ResNum, int &ResDen)
{
	int k;
	k = NOK(aDen, bDen);
	aNum *= k/aDen;
	bNum *= k/bDen;
	aDen = bDen = k;
	ResNum = aNum + bNum;
	ResDen = k;
}

void readBinFromFile (FILE *rf, int &numer, int &denom)
{
	string BinCode = "";
	int calcnum = 1;
	int calcden = 2;
	if (rf != NULL)
	{
		unsigned char buf = 0;
		int bit_count = 0;
		unsigned char bit = 0;
		string str_bit = "";
		while(1)
		{
  			buf = fgetc(rf);
  			if(feof(rf))
  				break;
			bit_count = 0;
  			for(; bit_count<8; bit_count++){
				bit = buf << bit_count;
				bit >>= 7;
				if (bit){
					BinCode += '1';
					flNumSum(numer, denom, calcnum, calcden, numer, denom);
				} else {
					BinCode += '0';
				}
				calcden *= 2;
			}
		}
		cout << BinCode << endl;
	}
}

void decalph (FILE *rf, int symnum)
{
	int lnum = 0;
	int lden = A[0].qdenom; // L
	
	int hnum = A[0].qdenom;
	int hden = A[0].qdenom; // H
	
	Rnumer = Rdenom = A[0].qdenom; // R
	
	int valnum = 0;
	int valden = 1;
	int i, j;
	
	readBinFromFile (rf, valnum, valden);
	for (i = 0; i < symnum; ++i)
	{
		for (j = 0; j < MSIZE; ++j)
		{
			int nlnum = -1 * lnum;
			int jnum = Rnumer * A[j].qnumer;
			int jden = Rdenom * A[j].qdenom;
			int j1num = Rnumer * A[j-1].qnumer;
			int j1den = Rdenom * A[j-1].qdenom;
			flNumSum(lnum, lden, jnum, jden, hnum, hden); // h = l + r*q
			if (j)
				flNumSum(lnum, lden, j1num, j1den, lnum, lden); // l = l + r*q
			flNumSum(hnum, hden, nlnum, lden, Rnumer, Rdenom); // r = h - l
			if (1)
				break;
		}
		cout << A[j].a;
	}
};
