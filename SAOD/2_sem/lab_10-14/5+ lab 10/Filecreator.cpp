#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	int num;
	int i = 0, j;
	char buff = 0;
	srand(time(NULL));
	FILE* pF = fopen("code.dat","wb+");
	while(i < 10000)
	{
		num = rand() % 20;
		if(!(num))
		{
			buff = buff + 1; 
		}
		buff += 48;
        ++i;
		fputc((int)buff,pF);
		buff = 0;
	}
	fclose(pF);
	return 0;
}
