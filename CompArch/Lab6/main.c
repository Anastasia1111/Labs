#include "hdchs.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	tIDECHS geom;
	int c, h, s;
	int flag = 1;
	while(flag)
	{
		printf("\nEnter geometry IDECHS:");
		printf("\n C: ");
		scanf("%d", &c);
		printf("\n H: ");
		scanf("%d", &h);
		printf("\n S: ");
		scanf("%d", &s);
		if(c > 0 && h > 0 && s > 0 && c < 65535 && h < 16 && s < 256)
			flag = 0;
		else printf("\n Wrong params");
	}
	geom.cylinder = c;
	geom.head = h;
	geom.sector = s;
	printf("%d %d %d", geom.cylinder, geom.head, geom.sector);
	double cap = geom.cylinder * geom.head * geom.sector / 2048.0 / 1024.0;
	printf("\n Capacity: %.3fGB", cap);
	
	
}
