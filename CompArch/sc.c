#include "sc.h"

#include <stdlib.h>
#include <stdio.h>

#define MASK(x) (1<<(x-1))
#define ramSize 100
int RAM[ramSize];
int REG;

int sc_memoryInit ()
{
	for(int i = 0; i < ramSize; ++i)
	{
		RAM[i] = 0;
	}
	return 0;
}

int sc_memorySet (int address, int value)
{
	int errFlag = 1;
	if(address > 0 && address < 99)
	{
		RAM[address] = value;
		errFlag = 0;
	}
	return errFlag;
}

int sc_memoryGet (int address, int *value)
{
	int errFlag = 1;
	if(address > 0 && address < 99)
	{
		value = RAM+address;
		errFlag = 0;
	}
	return errFlag;
}

int sc_memorySave (char *filename)
{
	FILE *f;
	f = fopen(filename, "wb");
	if(f == NULL)
	{
		return 1;
	}
	fwrite(RAM, sizeof(int), ramSize, f);
	fclose(f);
	return 0;
}

int sc_memoryLoad (char *filename)
{
	FILE *f;
	f = fopen(filename, "rb");
	if(f == NULL)
	{
		return 1;
	}
	fread(RAM, sizeof(int), ramSize, f);
	fclose(f);
	return 0;
}

int sc_regInit (void)
{
	REG = 0;
}

int sc_regSet (int register, int value)
{
	
}

int sc_regGet (int register, int *value)
{
	
}

int sc_commandEncode (int command, int operand, int *value)
{
	
} 

int sc_commandDecode (int value, int *command, int *operand)
{
	
}



