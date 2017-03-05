#include "sc.h"

#define REG_OVERFLOW 0x18
#define REG_ZERO_DIV 0x19
#define REG_OVERLIMIT_MEM 0x1A
#define REG_STEP_IGNORE 0x1B
#define REG_WR_COM 0x1C

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
	REG &= (~0)>>8;
	return 0;
}

int sc_regSet (int registr, int value)
{
	if(registr >= 0x18 && registr < 0x1D && value >= 0 && value < 2)
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
	if(registr >= 0x18 && registr < 0x1D && value != NULL)
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
	
	if((command == 0xA) || (command == 0xB) || (command == 0x14) || (command == 0x15) || 
	(command >= 0x1E && command <= 0x21) || (command >= 0x28 && command <= 0x4C))
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
	if((((value)>>14)&1) == 1)//command flag
	{
		sc_regSet(REG_WR_COM, 1);
		return 1; //not command
	}
	int dec_sevbit_mask = (value >> 7)& 0x7F;
	if((dec_sevbit_mask ) == 10 || ( dec_sevbit_mask ) == 11 || 
	( dec_sevbit_mask ) == 20 || ( dec_sevbit_mask ) == 21 || 
	(( dec_sevbit_mask ) >= 30 && ( dec_sevbit_mask ) <= 33) || 
	(( dec_sevbit_mask ) >= 40 && ( dec_sevbit_mask ) <= 76))
	{
		*command = value >> (8-1);
	} else {
		sc_regSet(REG_WR_COM, 1);
		return 2; // not existing command
	}
	*operand = value & 0x7F;
	return 0;
}
