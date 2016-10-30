#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

int SearchScan (char *haystack, int n, char *needle, int m);
int RabinKarp (char *haystack, int n, char *needle, int m);
int Hash(char* str, int m);

int C;

int main(void)
{
	setlocale(LC_ALL, "Russian");
	/****************/
	char haystack[] = {"Символ – элементарная единица, некоторый набор которых несет \n\
определенный смысл. В языке программирования С++ предусмотрено \n\
использование символьных констант. Символьная константа – это \n\
целочисленное значение (типа int) представленное в виде символа, \n\
заключённого в одинарные кавычки, например 'a'. В таблице ASCII \n\
представлены символы и их целочисленные значения.'"};
	char needle[] = {"символ"};
	printf("Haystack: ");
	puts(haystack);
	printf("Length: %i\n", strlen(haystack));
	printf("Needle: ");
	puts(needle);
	/****************/	
	int m;
	int i = 0;
	C = 0;
	/****************/
	while (1){
		m = SearchScan(haystack + i, strlen(haystack + i), needle, strlen(needle));
		if (m + i == strlen(haystack) - strlen(needle))
		{
			break;
		}
		printf("SearchScan: %i \n", m + i);
		i += m + 1;
	}
	printf("Numcomp: %i \n\n",C);
	/****************/
	i = 0;
	m = 0;
	C = 0;
	/****************/
	while (1){
		m = RabinKarp(haystack + i, strlen(haystack + i), needle, strlen(needle));
		if (m == -1)
		{
			break;
		}
		printf("RabinKarp: %i \n", m + i);
		i += m + 1;
	}
	printf("Numcomp: %i \n",C);
	/****************/
	system("PAUSE");
}

int SearchScan(char *haystack, int n, char *needle, int m)
{
	int i = -1, j;
	do {
		i++;
		j = 0;
		C++;
		while ( (j < m) && (haystack[i+j] == needle[j]) )
		{
			j++;
			C++;
		}
	} while ( (j != m) && (i < (n - m)) );
	return i;
}

int RabinKarp (char *haystack, int n, char *needle, int m)
{
	int hash_needle = Hash(needle, m);
	int hash_haystack = Hash(haystack, m);
	int i;
	for(i = 0; i < (n - m + 1); i++)
	{
		if (hash_haystack == hash_needle)
		{
			C += m;
			if (strncmp(haystack+i, needle, m) == 0)// ???
			{
				return i;
			}
		}
		hash_haystack = Hash(haystack + i + 1, m);
	}
	return -1;
}

int Hash(char* str, int m) 
{
	int h = 0;
	for (int i = 0; i < m; i++)
		h = h*256 + str[i];
	h = h % 17;
	return h;
}
