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
			fprintf (stderr, "Error[line %d]: Arithmetic expression is incorrect.\n", STRN);
		break;
		case 6:
			fprintf (stderr, "Error[line %d]: Number(s) in arithmetic expression is too big.\n", STRN);
		break;
		case 7:
			fprintf (stderr, "Error[line %d]: Bad variable.\n", STRN);
		break;
		case 8:
			fprintf (stderr, "Error[line %d]: GOTO has wrong number of line.\n", STRN);
		break;
		case 9:
			fprintf (stderr, "Error[line %d]: IF has wrong comparision.\n", STRN);
		break;
	}
	return;
}
