#include "sc.h"

#include <stdlib.h>
#include <stdio.h>

#define SET_FLAG_TRUE(x) |(1<<(x+24))
#define SET_FLAG_FALSE(x) &(1<<(x+24))
#define ramSize 100
int RAM[ramSize];
int REG;/* 0-14 = accumulator
		*16-22 = command pointer
		*24-28 = flag register
		* 	24 (code 1):overfilling
		*	25 (code 2):division on 0
		*	26 (code 3):exit over limits of memory
		* 	27 (code 4):step inpulses ignoring
		* 	28 (code 5):wrong command
		* */ 

int sc_memoryInit ()
{
	for(int i = 0; i < ramSize; ++i)
	{
		RAM[i] = 0;
	}
}

int sc_memorySet (int address, int value)
{
	if(address > 0 && address < 99)
	{
		RAM[address] = value;
	} else {
		sc_regSet(3, 1);
		return 1;
	}
	return 0;
}

int sc_memoryGet (int address, int *value)
{
	if(address > 0 && address < 99)
	{
		value = RAM+address;
	} else {
		sc_regSet(3, 1);
		return 1;
	}
	return 0;
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

int sc_regSet (int registr, int value)
{
	if(registr > 0 && registr < 6 && value > 0 && value < 2)
	{
		if(value == 1)
		{
			REG = (REG) SET_FLAG_TRUE(registr);
		} else {
			REG = (REG) SET_FLAG_FALSE(registr);
		}
	} else {
		return 1;
	}
	return 0;
}

int sc_regGet (int registr, int *value)
{
	if(registr > 0 && registr < 6)
	{
		
	} else {
		return 1;
	}
	return 0;
}

int sc_commandEncode (int command, int operand, int *value)
{
	
} 

int sc_commandDecode (int value, int *command, int *operand)
{
	
}



