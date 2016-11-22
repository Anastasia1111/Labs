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
		cout<<m<<endl;
		for (int i=l; i<r; i++){
			if (i<=m)
			{
				CodeWord[i] += '0';
			} else {
				CodeWord[i] += '1';
			}
		}
		/*for(int i = l; i < r; ++i)
		{
			cout<<left<<alphabet[i].ch<<" | ";
			cout<<setw(10)<<left<<(double)alphabet[i].prob<<" | ";
			cout<<setw(10)<<left<<CodeWord[i]<<" | ";
			cout<<left<<CodeWord[i].size()<<endl;
		}
		system("PAUSE");*/
		cout<<"from m="<<m<<" go to left"<<"(l="<<l<<",r="<<m<<")"<<endl;
		codeFano(l, m+1);
		cout<<"from m="<<m<<" go to right"<<"(l="<<m+1<<",r="<<r<<")"<<endl;
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
	
	/*FILE *pF;
	pF = fopen("encoding_results.dat","wb");
	
	if (pF != NULL)
	{
		char* DB = (char *)database;
		int size = sizeof(record)*DBSize;
		char buf = 0;
		char bit_count = 0;
		int CWSize = 0;
		for(int i=0; i<size; i++)
		{
			for(int j=0; j<CWNum; j++){
				if (DB[i]==alphabet[j].ch)
				{
					CWSize = CodeWord[j].size();
					for (int k=0; k<CWSize; k++){
						if (bit_count==8)
						{
							fputc((int)buf, pF);
							buf = 0;
							bit_count = 0;
						}
						if(CodeWord[j][k]=='1')
						{
							buf++;
						}
						buf <<= 1;
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
	
	system("PAUSE");
	fseek(pF, 0, SEEK_END);
	long size = ftell(pF);
	
	cout << "Size of encoding_results.dat: " << size << " bytes\n";

	fclose(pF);*/
	
	return CWNum;
}

main()
{
	int i, j;
	string message = "vvodi suda lubuy chush!1111adin 0451";
	
	int n = encode(message);
	int prob_sum = message.size();
	for(i = 0; i < n; ++i)
	{
		/*printf("%4c.  %1.4f  %s  %2i", alphabet[i].ch, alphabet[i].prob/prob_sum, CodeWord[i], CodeWord[i].size());
		printf("\n");*/
		cout<<left<<alphabet[i].ch<<" | ";
		cout<<setw(10)<<left<<(double)alphabet[i].prob/prob_sum<<" | ";
		cout<<setw(10)<<left<<CodeWord[i]<<" | ";
		cout<<left<<CodeWord[i].size()<<endl;
	}
	
	double h = 0, ml = 0, prob;
	for(i = 0; i < n; ++i)
	{
		prob = (double)alphabet[i].prob/prob_sum;
		h += -1*prob * log2(prob);
		ml += CodeWord[i].size() * prob;
	}
	printf("\nEntropia: %1.4f, Mid length: %1.4f",h,ml);
	
	system("pause");
	return 0;
}
