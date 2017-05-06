#include "translator.h"

int STRN = 0;

int main(int argc, char* argv[])
{
	char string[STR_SIZE];
	
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
		translate(string);
		STRN++;
	} while (1);
	fclose(in),
	fclose(out);
	return 0;
}
