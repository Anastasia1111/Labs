#include "Atranslator.h"

int translate(char *input, int *output)
{
	int memory = 0;
	int operand = 0;
	int i = 0;
	
	while(input[i] == ' ')
		i++;
	if((input[i]) == '\n' || input[i] == ';')// empty line
		return 100;

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
				memory *= 10;
				memory += (input[i] - '0');
				++i;
			break;
			default:
				error_log(4);
				return -1;
			break;
		}
	}
	if(memory > 99)
	{
		error_log(6);
		return -1;
	}
	
	if(input[i] == ' ')
		i++;
	else {
		error_log(4);
		return -1;
	}
	while(input[i] == ' ')
		i++;
	
	enum commands command;
	i += translate_command(input+i, &command); 
	if(command == NO_COM)
	{
		printf("this? ");
		error_log(5);
		return -1;
	}
	if(command == EQU)
	{
		while(input[i] == ' ')
			i++;
		while((input[i] != ' ') && (input[i] != ';'))
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
					operand <<= 4;
					operand += (input[i] - '0');
					++i;
				break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					operand <<= 4;
					operand += (input[i] - 'A' + 10);
					++i;
				break;
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
					operand <<= 4;
					operand += (input[i] - 'a' + 10);
					++i;
				break;
				default:
					error_log(7);
					return -1;
				break;
			}
		*output = operand;
		return memory;
	} else {
		if(command == HALT)
		{
			operand = 0;
			int icom = command;
			int res = sc_commandEncode(icom, operand, output);
			if(res != 0)
			{
				error_log(5);
				return -1;
			}
			return memory;
		}
		while(input[i] == ' ')
			i++;
		
		while((input[i] != ' ') && (input[i] != ';'))
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
					operand *= 10;
					operand += (input[i] - '0');
					++i;
				break;
				default:
					error_log(4);
					return -1;
				break;
			}
		int icom = command;
		int res = sc_commandEncode(icom, operand, output);
		if(res != 0)
		{
			error_log(5);
			return -1;
		}
		return memory;
	}
	return -1;
}

int translate_command(char *input, enum commands *output)
{
	*output = NO_COM;
	int n = 0;
	if(strncmp(input, "= ", 2) == 0)
	{
		*output = EQU;
		n = 2;
	}
	if(strncmp(input, "READ ", 5) == 0)
	{
		*output = READ;
		n = 5;
	}
	if(strncmp(input, "WRITE ", 6) == 0)
	{
		*output = WRITE;
		n = 6;
	}
	if(strncmp(input, "LOAD ", 5) == 0)
	{
		*output = LOAD;
		n = 5;
	}
	if(strncmp(input, "STORE ", 6) == 0)
	{
		*output = STORE;
		n = 6;
	}
	if(strncmp(input, "ADD ", 4) == 0)
	{
		*output = ADD;
		n = 4;
	}
	if(strncmp(input, "SUB ", 4) == 0)
	{
		*output = SUB;
		n = 4;
	}
	if(strncmp(input, "DIVIDE ", 7) == 0)
	{
		*output = DIVIDE;
		n = 7;
	}
	if(strncmp(input, "MUL ", 4) == 0)
	{
		*output = MUL;
		n = 4;
	}
	if(strncmp(input, "JUMP ", 5) == 0)
	{
		*output = JUMP;
		n = 5;
	}
	if(strncmp(input, "JNEG ", 5) == 0)
	{
		*output = JNEG;
		n = 5;
	}
	if(strncmp(input, "JZ ", 3) == 0)
	{
		*output = JZ;
		n = 3;
	}
	if(strncmp(input, "HALT", 4) == 0)
	{
		*output = HALT;
		n = 4;
	}
	if(strncmp(input, "RCR ", 4) == 0)
	{
		*output = RCR;
		n = 4;
	}
	if(strncmp(input, "RCCL ", 5) == 0)
	{
		*output = RCCL;
		n = 5;
	}
	return n;
}
