#include <stdlib.h>
#include <stdio.h>

void SearchScan (char *haystack, int n, char *needle, int m);
int RabinKarp (char *haystack, int n, char *needle, int m);

int main(void)
{
	
}

void SearchScan(char *haystack, int n, char *needle, int m)
{
	int i = -1, j;
	do {
		i++;
		j = 0;
		while ( (j < m) && (haystack[i+j] == needle[j]) )
		{
			j++;
		}
	} while ( (j != m) && (i < (n - m)) );
	return;
}

int RabinKarp (char *haystack, int n, char *needle, int m)
{
	int hash_needle = hash(needle, m);
	int hash_haystack = hash(haystack, n);
	int i;
	for(i = 0; i < (n - m + 1); i++)
	{
		if (hash_haystack == hash_needle)
		{
			if (strstr(haystack[i], needle) == haystack[i])// ???
			{
				return i;
			}
		}
		hash_haystack = hash(haystack[i + 1...i + m]);
	}
	return -1;
}
