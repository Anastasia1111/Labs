#include "Atranslator.h"

int STRN = 1;

int main(int argc, char* argv[])
{
	char string[STR_SIZE];
	int flag;
	int outmem;
	int i;
	for(i = 0; i < ramSize; ++i)
		BRAM[i] = 0;
	
	if(argc < 3)
	{
		error_log(1);
		return 1;
	}
	
	in = fopen(argv[1], "r");
	if(in == NULL)
	{
		error_log(2);
		return 1;
	}
	
	out = fopen(argv[2], "w");
	fwrite(BRAM, sizeof(int), ramSize, out);
	do {
		if(fgets(string, sizeof(string), in) == NULL)
		{
			if(feof(in) != 0)
			{
				break;
			} else {
				error_log(3);
				return 1;
			}
		}
		
		flag = translate(string, &outmem);
		if(flag == -1)
			return 1;
		STRN++;
		if(flag == 100)
			continue;
		if(flag >= 0 && flag <= 99)
		{
			fseek(out, flag*sizeof(int), SEEK_SET);
			fwrite(&outmem, sizeof(int), 1, out);
		}
	} while (1);
	fclose(in),
	fclose(out);
	return 0;
}
