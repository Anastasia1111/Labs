#include "Btranslator.h"

int Btranslate(char *input, int *output)
{
	int i = 0, j;
	int stringnum = 0;
	enum bcomm oper;
	
	while(input[i] == ' ')
		i++;
	while(input[i] != ' ')
	{
		switch(input[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				stringnum *= 10;
				stringnum += (input[i] - '0');
				++i;
			break;
			default:
				error_log(4);
				return -1;
			break;
		}
	}
	if(input[i] == ' ')
		i++;
	else {
		error_log(4);
		return -1;
	}
	while(input[i] == ' ')
		i++;
	i += command_translator(input + i, &oper);
	switch(oper)
	{
		case EMPTY:
			error_log(6);
			return -1;
		case REM:
			return 0;
		case INPUT:
			input(input + i);
			break;
		case OUTPUT:
			output(input + i);
			break;
		case LET:
			RPN(input + i);
			break;
		case IF:
			//if_function
			break;
		case GOTO:
			//jump
			break;
		case END:
			return 1;
	}
	
	return -1;
}

int command_translator(char *input, enum bcomm *output)
{
	*output = EMPTY;
	int n = 0;
	if(strncmp(input, "REM ", 4) == 0)
	{
		*output = REM;
		n = 4;
	}
	if(strncmp(input, "INPUT ", 6) == 0)
	{
		*output = INPUT;
		n = 6;
	}
	if(strncmp(input, "OUTPUT ", 7) == 0)
	{
		*output = OUTPUT;
		n = 7;
	}
	if(strncmp(input, "LET ", 4) == 0)
	{
		*output = LET;
		n = 4;
	}
	if(strncmp(input, "IF ", 3) == 0)
	{
		*output = IF;
		n = 3;
	}
	if(strncmp(input, "GOTO ", 5) == 0)
	{
		*output = GOTO;
		n = 5;
	}
	if(strncmp(input, "END", 3) == 0)
	{
		*output = END;
		n = 3;
	}
	/*if(strncmp(input, "+ ", 2) == 0)
	{
		*output = PLUS;
		n = 2;
	}
	if(strncmp(input, "- ", 2) == 0)
	{
		*output = MINUS;
		n = 2;
	}
	if(strncmp(input, "* ", 2) == 0)
	{
		*output = MULTI;
		n = 2;
	}
	if(strncmp(input, "/ ", 2) == 0)
	{
		*output = DIVIS;
		n = 2;
	}
	if(strncmp(input, "= ", 2) == 0)
	{
		*output = EQUAL;
		n = 2;
	}
	if(strncmp(input, "> ", 2) == 0)
	{
		*output = BIG;
		n = 2;
	}
	if(strncmp(input, "< ", 2) == 0)
	{
		*output = LES;
		n = 2;
	}
	if(strncmp(input, "== ", 3) == 0)
	{
		*output = EQUALITY;
		n = 3;
	}
	if(input[i] == '(')
	{
		*output = LBRACK;
		n = 1;
	}
	if(input[i] == ')')
	{
		*output = RBRACK;
		n = 1;
	}
	if(input[i] >= 'A' && input[i] <= 'Z' && input[i+1] == ' ')
	{
		*output = VAR;
		n = 2;
	}*/
	return n;
}
