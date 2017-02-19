#include "sc.h"

#define ramSize 100
int RAM[ramSize];
int REG = 0;/* 0-14 = accumulator
		*16-22 = command pointer
		*24-28 = flag register
		* 	24 (code 1):overfilling
		*	25 (code 2):division on 0
		*	26 (code 3):exit over limits of memory
		* 	27 (code 4):step inpulses ignoring
		* 	28 (code 5):wrong command
		* */ 

#define SET_FLAG_TRUE(x) |(1<<(x + 24))
#define SET_FLAG_FALSE(x) &(~(1<<(x + 24)))
#define GET_FLAG(val,x) (((val)>>(x + 24))&1)
#define GET_FLAG_COMMAND(val) (((val)>>14)&1)
#define DECODE_SEVENBIT_MASK(x) (x)&(~(~(0)<<7))
#define FLAG_INIT(x) (x)&(~(0)>>8)

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
		sc_regSet(3, 1);
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
	REG = FLAG_INIT(REG);
	return 0;
}

int sc_regSet (int registr, int value) // 0 <= registr <= 4 
{
	if(registr >= 0 && registr < 5 && value >= 0 && value < 2)
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

int sc_regGet (int registr, int *value) // 0 <= registr <= 4
{
	if(registr >= 0 && registr < 5 && value != NULL)
	{
		*value = GET_FLAG(REG, registr );
	} else {
		return 1;
	}
	return 0;
}

int sc_commandEncode (int command, int operand, int *value)
{		
	if(operand < 0 && operand >= 256)
		return 2; // error with operand
		
	if(value == NULL)
		return 3; // error with value
	
	if(command == 10 || command == 11 || command == 20 || command == 21 || 
	(command >= 30 && command <= 33) || (command >= 40 && command <= 76))
	{	
		// encoding
		*value = 0;
		*value = (*value) | (command << (8-1));
		*value = (*value) | (operand << (1-1));
	} else {
		return 1;
	}
	return 0;
} 

int sc_commandDecode (int value, int *command, int *operand)
{
	if(GET_FLAG_COMMAND(value) == 1)
	{
		REG = (REG) SET_FLAG_TRUE(5);
		return 1; //not command
	}
	
	if((DECODE_SEVENBIT_MASK(value >> (8-1)) ) == 10 || ( DECODE_SEVENBIT_MASK(value >> (8-1)) ) == 11 || 
	( DECODE_SEVENBIT_MASK(value >> (8-1)) ) == 20 || ( DECODE_SEVENBIT_MASK(value >> (8-1)) ) == 21 || 
	(( DECODE_SEVENBIT_MASK(value >> (8-1)) ) >= 30 && ( DECODE_SEVENBIT_MASK(value >> (8-1)) ) <= 33) || 
	(( DECODE_SEVENBIT_MASK(value >> (8-1)) ) >= 40 && ( DECODE_SEVENBIT_MASK(value >> (8-1)) ) <= 76))
	{
		*command = value >> (8-1);
	} else {
		REG = (REG) SET_FLAG_TRUE(5);
		return 2; // not existing command
	}
	*operand = ( DECODE_SEVENBIT_MASK(value >> (1-1)) );
	return 0;
}



