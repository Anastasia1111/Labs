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
void encodeInFile(string msg, int CWNum);
void decode();

//*************************************************

main()
{
	setlocale(LC_ALL, "Russian");
	int i;
	A = new alph[size];
	codewords = new string[size];
	string mess = "ggggjhsgjkhgkjhajkgahgkjhgk57387539867&^%&^$%$gfuiuhghojhd/lor;o/trkgsjopistjoisptiogpssgijopsgtiojsgtogoskpgimosgkomgojsmtsoijmgsjiogsojgmsoigmsogjmsoigpjmsoipgmsieutgmsoitpgmsgijmgsipjmgismsoigmsigsigmsuignmusigmsoispmgsiobmsbs,boisbm,oisibmbosibmsoimsoipbmbs7oip6msb5iops4mb3iopsbmsobipmbsopim6748u6839u63980628096t682mt90umg9us0nu89syngs9mg9sugmn9u0sgmg09ïâïëäâüòïëâòüïåâïüëâäëïüëäâüòåùîöóòåùöòïàïøûïò øûïòûãøåïØÃĞÒØÃÈĞØÍÌÏÈÙÍÌÈÙ*ÈÙÀÈÒÀÀÙÃÀÈÒÃÙÀÈÃÙÀØØÈÀÃÀÈ5258905890272697209676262086708uiaghopuayhouapghuagpohugaipohgug%^$#^HKJHKJHKJHJFJNBMGGNGÒÏÛÒÏÄÏÒÄÎÛÈÒÌÜÛÆÄÏÜÆÛÙÅÎjahkajghkajghkajlghkjaghkjagkjabnjkabnkajlbnlahbéöóêåíãøùçùúäîáüìòèÿôö";
	
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
	int n = 0;
	while(A[n].p){
			++n;
		}
	encodeInFile(mess,n);
	printf("\nEncoded.\n");
	system("PAUSE");
	decode();
	printf("\nDecoded.\n");
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
		if(j < 0)
			j += 256;
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
	
	A[0].p != 0.0 ? A[0].l = (int)(ceil(fabs(log2(A[0].p))) + 1) : A[0].l = 0;
	for (i = 1; i < size; ++i)
	{
		A[i].q = A[i-1].q + A[i-1].p;
		A[i].p != 0.0 ? A[i].l = (int)(ceil(fabs(log2(A[i].p))) + 1) : A[i].l = 0;
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
		if(A[i].p != 0.0)
		{
			printf("%4i. %c:  prob: %1.5f ", i, A[i].a, A[i].p);
			cout << codewords[i] << " Length:" << codewords[i].length() << endl;
		}
	}
}

bool compar(alph a, alph b)
{
	return a.p < b.p;
};

void encodeInFile(string msg, int CWNum){
	int str_length; 
	str_length = msg.length();
	
	FILE *pF;
	pF = fopen("encoding_results.dat","wb");
	
	if (pF != NULL)
	{
		char buf = 0;
		char bit_count = 0;
		int CWsize = 0;
		for(int i=0; i<str_length; i++)
		{
			for(int j=0; j<CWNum; j++){
				if (msg[i]==A[j].a)
				{
					CWsize = codewords[j].length();
					for (int k=0; k<CWsize; k++){
						if (bit_count==8)
						{
							fputc((int)buf, pF);
							buf = 0;
							bit_count = 0;
						}
						buf <<= 1;
						if(codewords[j][k]=='1')
						{
							buf++;
						}
						bit_count++;
					}
				}
			}
		}
		if(bit_count!=0)
		{
			for(int j=bit_count; j<8; j++)
				buf<<=1;
			fputc((int)buf, pF);
			buf = 0;
			bit_count = 0;
		}
	} else {
		puts("\nERROR! Something unexpected caused a plem! Encoding results wastn't created!\n");
		system("PAUSE");
		exit(1);
	}
	
	fseek(pF, 0, SEEK_END);
	int fsize = ftell(pF);
	
	cout << "str_length (virtual) of uncoded file: "<<str_length<<" bytes\nstr_length of encoding_results.dat: " << fsize << " bytes\n";

	fclose(pF);
}

void decode()
{
	if (A==NULL || codewords==NULL){
		system("CLS");
		puts("Message hasn't encoded yet!\n");
		system("PAUSE");
		return;
	}
	
	FILE *pF;
	pF = fopen("encoding_results.dat","rb");
	
	if (pF != NULL)
	{
		int CWNum = 0;
		while(A[CWNum].p){
			CWNum++;
		}
		unsigned char buf = 0;
		int bit_count = 0;
		unsigned char bit = 0;
		string str_bit = "";
		while(1)
		{
  			buf = fgetc(pF);
  			if(feof(pF))
  				break;
			bit_count = 0;
  			for(; bit_count<8; bit_count++){
				bit = buf << bit_count;
				bit >>= 7;
				if (bit){
					str_bit += '1';
				} else {
					str_bit += '0';
				}
				for(int j=0; j<CWNum; j++){
					if (!str_bit.compare(codewords[j])){
						cout<<A[j].a;
						str_bit.clear();
					}
				}
			}
		}
		cout<<endl;
	}
	fclose(pF);
}
