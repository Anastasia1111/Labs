#include "SimpleComputer.h"

int ALU(int command, int operand)
{
	int buf, minbuf;
	int a;
	int bAccum = Accum;
	int bRAM = RAM[operand];
	
	int Accmin = (bAccum >> 14) & 1;
	int RAMmin = (bRAM >> 13) & 1;
	if(Accmin)
		bAccum *= -1;
	if(RAMmin)
		bRAM *= -1;
	int res;
	switch(command) {
		case ADD:
			res = bAccum + bRAM;
			if(res >= 0x3FFF || res <= -0x3FFF)
			{
				sc_regSet(REG_OVERFLOW, 1);
				return -1;
			}
			Accum = 0;
			Accum += (res & 0x3FFF);
			if(res < 0)
				Accum |= 1 << 14;
		break;
		case SUB:
			res = bAccum - bRAM;
			if(res >= 0x3FFF || res <= -0x3FFF)
			{
				sc_regSet(REG_OVERFLOW, 1);
				return -1;
			}
			Accum = 0;
			Accum += (res & 0x3FFF);
			if(res < 0)
				Accum |= 1 << 14;
		break;
		case DIVIDE:
			if(bRAM == 0)
			{
				sc_regSet(REG_ZERO_DIV, 1);
				return -1;
			}
			res = bAccum / bRAM;
			Accum = 0;
			Accum += (res & 0x3FFF);
			if(res < 0)
				Accum |= 1 << 14;
		break;
		case MUL:
			res = bAccum * bRAM;
			if(res >= 0x3FFF || res <= -0x3FFF)
			{
				sc_regSet(REG_OVERFLOW, 1);
				return -1;
			}
			Accum = 0;
			Accum += (res & 0x3FFF);
			if(res < 0)
				Accum |= 1 << 14;
		break;
		case RCR:
			bRAM = RAM[operand] & 0x3FFF;
			buf = (bRAM & 1) << 14;
			Accum = 0;
			Accum = bRAM >> 1;
			Accum += buf;
		break;
		case RCCL:
			if(bAccum < 0)
				bAccum *= -1;
			a = bAccum % 15;
			bRAM = RAM[operand] & 0x3FFF;
			for(int i = 0; i < a; ++i)
			{
				buf = (bRAM & (1 << 14)) >> 14;
				Accum = (bRAM << 2) & 0x3FFF;
				Accum += buf;
			}
		break;
	}
	return 0;
}

int CU()
{
	char out[10];
	int value, command, operand, n, i;
	sc_memoryGet(InstCount, &value);
	if(sc_commandDecode(value, &command, &operand) != 0)
	{
		sc_regSet(REG_WR_COM, 1);
		return -1;
	}
	
	if(command >= ADD && command <= MUL || command == RCR || command == RCCL)
		return ALU(command, operand);
	else
	{
		if(command == READ)
		{
			return setInput(operand);
		}
		
		if(command == WRITE)
		{
			if(operand < 0 || operand > 99)
			{
				sc_regSet(REG_OVERLIMIT_MEM, 1);
				return -1;
			}
			if(RAM[operand] > 0x1FFF)
				n = sprintf(out, "-%04X", (RAM[operand] & 0x1FFF));
			else
				n = sprintf(out, " %04X", (RAM[operand] & 0x1FFF));
			mt_gotoXY(24, 8);
			write(STDOUT_FILENO, out, n);
			return 0;
		}
		
		if(command == LOAD)
		{
			if(operand < 0 || operand > 99)
			{
				sc_regSet(REG_OVERLIMIT_MEM, 1);
				return -1;
			}
			Accum = RAM[operand];
			return 0;
		}
		
		if(command == STORE)
		{
			if(operand < 0 || operand > 99)
			{
				sc_regSet(REG_OVERLIMIT_MEM, 1);
				return -1;
			}
			RAM[operand] = Accum;
			return 0;
		}
		
		if(command == JUMP)
		{
			if(operand >= 0 && operand <= 99)
				InstCount = operand;
			else
			{
				sc_regSet(REG_OVERLIMIT_MEM, 1);
				return -1;
			}
			return 0;
		}
		
		if(command == JNEG)
		{
			if(Accum < 0)
				if(operand >= 0 && operand <= 99)
					InstCount = operand;
				else
				{
					sc_regSet(REG_OVERLIMIT_MEM, 1);
					return -1;
				}
			return 0;
		}
		
		if(command == JZ)
		{
			if(Accum == 0)
				if(operand >= 0 && operand <= 99)
					InstCount = operand;
				else
				{
					sc_regSet(REG_OVERLIMIT_MEM, 1);
					return -1;
				}
			return 0;
		}
		
		if(command == HALT)
		{
			return 1;
		}
	}
	return -1;
}

int setInput(int operand)
{
	mt_gotoXY(23, 7);
	write(STDOUT_FILENO, "      ", 6);
	mt_gotoXY(23, 7);
	int buf = 0;
	int minflag = 0;
	for(int i = 1; i < 5; ++i)
	{
		enum keys subbut;
		rk_readkey(&subbut);
		
		char mem;
		
		switch(subbut)
		{
			case key_min:
				if(i == 1)
				{
					mem = '-';
					write(STDOUT_FILENO, &mem, 1);
					minflag = 1;
				}
				i--;
				continue;
			break;
			case key_0:
				mem = '0';
				write(STDOUT_FILENO, &mem, 1);
				mem = 0;
				break;
			case key_1:
				mem = '1';
				write(STDOUT_FILENO, &mem, 1);
				mem = 1;
				break;
			case key_2:
				mem = '2';
				write(STDOUT_FILENO, &mem, 1);
				mem = 2;
				break;
			case key_3:
				mem = '3';
				write(STDOUT_FILENO, &mem, 1);
				mem = 3;
				break;
			case key_4:
				mem = '4';
				write(STDOUT_FILENO, &mem, 1);
				mem = 4;
				break;
			case key_5:
				mem = '5';
				write(STDOUT_FILENO, &mem, 1);
				mem = 5;
				break;
			case key_6:
				mem = '6';
				write(STDOUT_FILENO, &mem, 1);
				mem = 6;
				break;
			case key_7:
				mem = '7';
				write(STDOUT_FILENO, &mem, 1);
				mem = 7;
				break;
			case key_8:
				mem = '8';
				write(STDOUT_FILENO, &mem, 1);
				mem = 8;
				break;
			case key_9:
				mem = '9';
				write(STDOUT_FILENO, &mem, 1);
				mem = 9;
				break;
			case key_a:
				mem = 'A';
				write(STDOUT_FILENO, &mem, 1);
				mem = 10;
				break;
			case key_b:
				mem = 'B';
				write(STDOUT_FILENO, &mem, 1);
				mem = 11;
				break;
			case key_c:
				mem = 'C';
				write(STDOUT_FILENO, &mem, 1);
				mem = 12;
				break;
			case key_d:
				mem = 'D';
				write(STDOUT_FILENO, &mem, 1);
				mem = 13;
				break;
			case key_e:
				mem = 'E';
				write(STDOUT_FILENO, &mem, 1);
				mem = 14;
				break;
			case key_f:
				mem = 'F';
				write(STDOUT_FILENO, &mem, 1);
				mem = 15;
				break;
			default: 
				i--;
				continue;
				break;
		}
		buf <<= 4;
		buf += mem;
	}
	if(buf < 0 || buf > 0x1FFF)
	{
		sc_regSet(REG_OVERFLOW, 1);
		return -1;
	}
	if(minflag)
		buf |= (1 << 13);
	return sc_memorySet(operand, buf);
}
