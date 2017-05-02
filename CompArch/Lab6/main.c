#include "hdchs.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	tCHS a;
	tLBA b;
	int x, y, z;
	scanf("%d %d %d", &x, &y, &z);
	a.sector = (unsigned char)x;
	a.head = (unsigned char)y;
	a.cylinder = (unsigned short int)z;
	g_chs2lba(a, &b);
	printf("toLBA: %d", b.size);
	
}
