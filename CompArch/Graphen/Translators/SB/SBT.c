#include "Btranslator.h"

int STRN = 1;

int main(int argc char* argv[])
{
	int i;
	char ** string;
	int outmem;
	
	for(i = 0; i < ramSize; ++i)
		BRAM[i] = 0;
	string = (char **) calloc(200, sizeof(char *));
	for(i = 0; i < 200; ++i)
		string[i] = (char *) calloc(STR_SIZE, sizeof(char));
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
		if(fgets(string[i], sizeof(string[i]), in) == NULL)
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
	
	for(i = 0; i < 200, ++i)
		free(string[i]);
	free(string);
	
	fclose(in),
	fclose(out);
	return 0;
}
