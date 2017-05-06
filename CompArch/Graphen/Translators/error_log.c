#include "translator.h"

void error_log(int code)
{
	switch(code)
	{
		case 1:
			fprintf (stderr, "Error: Too few arguments for translator.\n");
		break;
		case 2:
			fprintf (stderr, "Error: input file doesn't exist.\n");
		break;
		case 3:
			fprintf (stderr, "Error: cannot read input file.\n");
		break;
		case 4:
			fprintf (stderr, "Error:[string %d]: no number of a memory cell.", STRN);
		break;
		case 5:
			fprintf (stderr, "Error:[string %d]: Wrong command.", STRN);
		break;
		case 6:
			fprintf (stderr, "Error:[string %d]: Too big operand.", STRN);
		break;
		case 7:
			fprintf (stderr, "Error:[string %d]: Wrong hex operand.", STRN);
		break;
	}
	return;
}
