#include "translator.h"

int translate(char *input, int *output)
{
	int memory = 0;
	int operand = 0;
	int i = 0;
	
	while(input[i] == ' ')
		i++;
	if((input[i]) == '\n')// empty line
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
				memory += (input[i] - '0');
				memory *= 10;
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
	translate_command(input+i, &command); 
	if(command == NO_COM)
	{
		error_log(5);
		return 1;
	}
	if(command == EQU)
	{
		while(input[i] == ' ')
			i++;
		while(input[i] != ' ')
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
					operand += (input[i] - '0');
					operand *= 10;
					++i;
				break;
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
					operand += (input[i] - 'A' + 10);
					operand <<= 4;
					++i;
				break;
				case 'a':
				case 'b':
				case 'c':
				case 'd':
				case 'e':
				case 'f':
					operand += (input[i] - 'a' + 10);
					operand <<= 4;
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
		while(input[i] == ' ')
			i++;
		
		while(input[i] != ' ')
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
					operand += (input[i] - '0');
					operand *= 10;
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
	if(strncmp(input, "= ", 5) == 0)
		*output = EQU;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "WRITE ", 6) == 0)
		*output = WRITE;
	if(strncmp(input, "LOAD ", 5) == 0)
		*output = LOAD;
	if(strncmp(input, "STORE ", 6) == 0)
		*output = STORE;
	if(strncmp(input, "ADD ", 4) == 0)
		*output = ADD;
	if(strncmp(input, "SUB ", 4) == 0)
		*output = SUB;
	if(strncmp(input, "DIVIDE ", 7) == 0)
		*output = DIVIDE;
	if(strncmp(input, "MUL ", 4) == 0)
		*output = MUL;
	if(strncmp(input, "JUMP ", 5) == 0)
		*output = JUMP;
	if(strncmp(input, "JNEG ", 5) == 0)
		*output = JNEG;
	if(strncmp(input, "JZ ", 5) == 0)
		*output = JZ;
	if(strncmp(input, "HALT ", 5) == 0)
		*output = HALT;
	if(strncmp(input, "RCR ", 5) == 0)
		*output = RCR;
	if(strncmp(input, "RCCL ", 5) == 0)
		*output = RCCL;
	return 0;
}
