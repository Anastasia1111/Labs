#include "Btranslator.h"

int Btranslate(char *input)
{
	int i = 0, j;
	int stringnum = 0;
	enum bcomm oper;
	struct bcomlist *com;
	com = (struct bcomlist *)malloc(sizeof(struct bcomlist));
	if (bhead != NULL)
		btail->next = com;
	else
		bhead = com;
	
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
			case '\n':
				return 100;
			default:
				error_log(4);
				return -1;
			break;
		}
	}
	
	com->number = stringnum;
	com->anum = COMNUM;
	
	if(input[i] == ' ')
		i++;
	else {
		error_log(4);
		return -1;
	}
	while(input[i] == ' ')
		i++;
	i += command_translator(input + i, &oper);
	com->oper = oper;
	int ret = 0;
	switch(oper)
	{
		case EMPTY:
			error_log(6);
			return -1;
		case REM:
			return 0;
		case INPUT:
			ret = InOutput(input + i, 1);
			break;
		case OUTPUT:
			ret = InOutput(input + i, 0);
			break;
		case LET:
			ret = RPN(input + i);
			break;
		case IF:
			ret = IfOper(input + i);
			break;
		case GOTO:
			ret = GoTo(input + i);
			break;
		case END:
			end();
			return 1;
	}
	btail = com;
	return ret;
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
	return n;
}
