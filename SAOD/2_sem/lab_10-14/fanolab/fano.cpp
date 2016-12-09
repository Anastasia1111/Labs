#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct chr
{
	int prob;
	unsigned char ch;
};

chr* alphabet = NULL;
string* CodeWord = NULL;

bool comparator(chr a, chr b)
{
	return a.prob<b.prob;
}

int find_probability(string msg)
{
	int size = msg.size();
	for (int i=0; i<size; i++){
		alphabet[msg[i]].prob++;
	}
	std::sort(alphabet, alphabet+256, comparator);
	std::reverse(alphabet, alphabet+256);
	
	int real_num = 0;
	while(alphabet[real_num].prob){
		real_num++;
	}
	return real_num;
}

int med(int l, int r)
{
	int sumL = 0;
	for(int i=l; i<r-1; i++){
		sumL += alphabet[i].prob;
	}
	int sumR = alphabet[r-1].prob;
	char m = r-1;
	while(sumL>=sumR)
	{
		m--;
		sumL -= alphabet[m].prob;
		sumR += alphabet[m].prob;
	}
	return m;
}

void codeFano(int l, int r)
{
	if (l<r-1)
	{
		int m = med(l,r);
		for (int i=l; i<r; i++){
			if (i<=m)
			{
				CodeWord[i] += '0';
			} else {
				CodeWord[i] += '1';
			}
		}
		codeFano(l, m+1);
		codeFano(m+1, r);
	}
}

int encode(string msg)
{
	alphabet = new chr[256];
		
	for (int i=0; i<256; i++){
		alphabet[i].prob = 0;
		alphabet[i].ch = i;
	}
	
	int CWNum = find_probability(msg);
	
	CodeWord = new string[CWNum];
	
	for (int i=0; i<CWNum; i++){
		CodeWord[i] = "";
	}
	
	codeFano(0,CWNum);
	
	return CWNum;
}

void encodeInFile(string msg, int CWNum){
	FILE *pF;
	pF = fopen("encoding_results.dat","wb");
	int size = msg.size();
	if (pF != NULL)
	{
		char buf = 0;
		char bit_count = 0;
		int CWSize = 0;
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<CWNum; j++){
				if (msg[i]==alphabet[j].ch)
				{
					CWSize = CodeWord[j].size();
					for (int k=0; k<CWSize; k++){
						if (bit_count==8)
						{
							fputc((int)buf, pF);
							buf = 0;
							bit_count = 0;
						}
						buf <<= 1;
						if(CodeWord[j][k]=='1')
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
		puts("\nERROR! Something unexpected caused a problem! Encoding results wastn't created!\n");
		system("PAUSE");
		exit(1);
	}
	
	fseek(pF, 0, SEEK_END);
	int fsize = ftell(pF);
	
	cout << "Size (virtual) of uncoded file: "<<size<<" bytes\nSize of encoding_results.dat: " << fsize << " bytes\n";
	cout << "compressing:" << (double)fsize/size << endl;
	fclose(pF);
}

void decode()
{
	if (alphabet==NULL || CodeWord==NULL){
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
		while(alphabet[CWNum].prob){
			CWNum++;
		}
		unsigned char buf = 0;
		int bit_count = 0;
		unsigned char bit = 0;
		string str_bit = "";
		while(!feof(pF))
		{
  			buf = fgetc(pF);
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
					if (!str_bit.compare(CodeWord[j])){
						cout<<alphabet[j].ch;
						str_bit = "";
					}
				}
			}
		}
		cout<<endl;
	}
	fclose(pF);
	
	system("PAUSE");
}

main()
{
	int i, j;
	string message = "cout << mess << endl << mess.length() << endl;\n\
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

	int n = encode(message);
	int msg_size = message.size();
	
	cout<<" | A |     P      |    code    |  L  |"<<endl;
	cout<<" +---+------------+------------+-----+"<<endl;
	for(i = 0; i < n; ++i)
	{
		cout<<" | "<<left<<alphabet[i].ch<<" | ";
		cout<<setw(10)<<left<<(double)alphabet[i].prob/msg_size<<" | ";
		cout<<setw(10)<<left<<CodeWord[i]<<" | ";
		cout<<setw(3)<<left<<CodeWord[i].size()<<" | "<<endl;
		cout<<" +---+------------+------------+-----+"<<endl;
	}
	
	double h = 0, ml = 0, prob_sum = 0, prob;
	for(i = 0; i < n; ++i)
	{
		prob = (double)alphabet[i].prob/msg_size;
		h += -1*prob * log2(prob);
		ml += CodeWord[i].size() * prob;
		prob_sum += prob; 
	}
	printf("Sum of probabilities: %1.4f\nEntropia: %1.4f, Mid length: %1.4f\n",prob_sum,h,ml);
	printf("entropia / 8: %f\n", h / 8);
	
	encodeInFile(message,n);
	system("PAUSE");
	decode();
	
	system("pause");
	return 0;
}
