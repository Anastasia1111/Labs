#include "../headers/sc.h"

char REG = 0;
char InstCount = 0;
short int Accum = 0;

int sc_memoryInit ()
{
	int i;
	for(i = 0; i < ramSize; ++i)
	{
		RAM[i] = 0;
	}
	return 0;
}

int sc_memorySet (int address, int value)
{
	if(address >= 0 && address <= 99)
	{
		RAM[address] = value;
	} else {
		sc_regSet(REG_OVERLIMIT_MEM, 1);
		return 1;
	}
	return 0;
}

int sc_memoryGet (int address, int *value)
{
	if(address >= 0 && address <= 99 && value != NULL)
	{
		*value = RAM[address];
	} else {
		sc_regSet(REG_OVERLIMIT_MEM, 1);
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
	return 0;
}

int sc_regSet (int registr, int value)
{
	if(registr >= REG_OVERFLOW && registr <= REG_WR_COM && value >= 0 && value < 2)
	{
		if(value == 1)
		{
			REG |= 0x1<<registr;
		} else {
			REG &= ~(0x1<<registr);
		}
	} else {
		return 1;
	}
	return 0;
}

int sc_regGet (int registr, int *value) 
{
	if(registr >= REG_OVERFLOW && registr <= REG_WR_COM && value != NULL)
	{
		*value = (REG>>registr)&(0x01);
	} else {
		return 1;
	}
	return 0;
}

int sc_commandEncode (int command, int operand, int *value)
{		
	if(operand < 0 || operand >= 128)
		return 2; // error with operand
		
	if(value == NULL)
		return 3; // error with value
	
	int flag = 0;
	for(enum commands i = READ; i <= RCCL; ++i)
		if(command == i)
			flag = 1;
	
	if(flag == 1)
	{	
		// encoding
		*value = 0;
		*value = (*value) | (command << 7);
		*value = (*value) | operand;
	} else {
		return 1;
	}
	return 0;
} 

int sc_commandDecode (int value, int *command, int *operand)
{	
	if(((value)>>14) != 0)//command flag
	{
		sc_regSet(REG_WR_COM, 1);
		return 1; //not command
	}
	
	int dec_sevbit_mask = (value >> 7)& 0x7F;
	int flag = 0;
	for(enum commands i = READ; i <= RCCL; ++i)
		if(dec_sevbit_mask == i)
			flag = 1;
	
	if(flag == 1)
	{
		*command = value >> 7;
	} else {
		sc_regSet(REG_WR_COM, 1);
		return 2; // not existing command
	}
	*operand = value & 0x7F;
	return 0;
}
