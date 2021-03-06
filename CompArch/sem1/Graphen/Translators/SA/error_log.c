#include "Atranslator.h"

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
			fprintf (stderr, "Error:[line %d]: no number of a memory cell.\n", STRN);
		break;
		case 5:
			fprintf (stderr, "Error:[line %d]: Wrong command.\n", STRN);
		break;
		case 6:
			fprintf (stderr, "Error:[line %d]: Too big operand.\n", STRN);
		break;
		case 7:
			fprintf (stderr, "Error:[line %d]: Wrong hex operand.\n", STRN);
		break;
		case 8:
			fprintf (stderr, "Error:[line %d]: Too big value for cell.\n", STRN);
		break;
	}
	return;
}
