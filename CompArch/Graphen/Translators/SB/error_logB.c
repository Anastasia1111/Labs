#include "Btranslator.h"

void error_log(int code)
{
	switch(code)
	{
		case 1:
			fprintf (stderr, "Error: Too few arguments for translator.\n");
		break;
		case 2:
			fprintf (stderr, "Error: Input file doesn't exist.\n");
		break;
		case 3:
			fprintf (stderr, "Error: Can not read input file.\n");
		break;
		case 4:
			fprintf (stderr, "Error:[line %d]: The line begins not with number.\n", STRN);
		break;
		case 5:
			fprintf (stderr, "Error: Arithmetic expression is incorrect\n");
		break;
	}
	return;
}
