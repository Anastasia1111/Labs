#include "translator.h"

int translate(char *input)
{
	int memory = 0;
	int i = 0;
	
	while(input[i] == ' ')
		i++;
	if(input[i] == "\n")// empty line
		return 0;

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
	
	if(input[i] == ' ')
		i++;
	else {
		error_log(4);
		return -1;
	}
	while(input[i] == ' ')
		i++;
	
	enum commands command;
	int flag = translate_command(input+i, &command); 
	
	
	return 0;
}

int translate_command(char *input, enum commands *output)
{
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "WRITE ", 5) == 0)
		*output = READ;
	if(strncmp(input, "LOAD ", 5) == 0)
		*output = READ;
	if(strncmp(input, "STORE ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
	if(strncmp(input, "READ ", 5) == 0)
		*output = READ;
		
		
	return 0;
}
