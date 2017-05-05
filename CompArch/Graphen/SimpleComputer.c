#include "SimpleComputer.h"

void write_ram(int x, int y)
{
	char mem[6];
	int com, oper, n;
	int value = 0;
	int flag, flagprev;
	
	mt_gotoXY(x+2, y*6 + 2);
	sc_regGet(REG_WR_COM, &flagprev);
	sc_memoryGet(x * 10 + y, &value);
	flag = sc_commandDecode(value, &com, &oper);
	if(flag == 0)
	{
		n = sprintf(mem, "+%02X%02X", com, oper);
		write(STDOUT_FILENO, mem, n);
	}
	else
	{
		value &= ~(1 << 14);
		n = sprintf(mem, " %04X", value);
		write(STDOUT_FILENO, mem, n);
		sc_regSet(REG_WR_COM, flagprev);
	}
};

void big_window()
{
	mt_gotoXY(14, 2);
	char mem[6];
	int com, oper, n, i, j;
	int value = 0;
	int flag, flagprev;
	
	sc_memoryGet(InstCount, &value);
	sc_regGet(REG_WR_COM, &flagprev);
	flag = sc_commandDecode(value, &com, &oper);
	if(!flag)
		n = sprintf(mem, "+%02X%02X ", com, oper);
	else
	{
		value &= ~(1 << 14);
		n = sprintf(mem, " %04X ", value);
		sc_regSet(REG_WR_COM, flagprev);
	}
	if(mem[0] == '+')
	{
		int num[2] = _P_;
		bc_printbigchar(num, 14, 2, LRED, GREEN);
	}
	else
	{
		int num[2] = {0x0, 0x0};
		bc_printbigchar(num, 14, 2, LRED, GREEN);
	}
	for(i = 1; i < 5; ++i)
	{
		int num[2];
		switch(mem[i])
		{
			
			case '0':
				num[0] = _0_0_;
				num[1] = _0_1_;
				break;
			case '1':
				num[0] = _1_0_;
				num[1] = _1_1_;
				break;
			case '2':
				num[0] = _2_0_;
				num[1] = _2_1_;
				break;
			case '3':
				num[0] = _3_0_;
				num[1] = _3_1_;
				break;
			case '4':
				num[0] = _4_0_;
				num[1] = _4_1_;
				break;
			case '5':
				num[0] = _5_0_;
				num[1] = _5_1_;
				break;
			case '6':
				num[0] = _6_0_;
				num[1] = _6_1_;
				break;
			case '7':
				num[0] = _7_0_;
				num[1] = _7_1_;
				break;
			case '8':
				num[0] = _8_0_;
				num[1] = _8_1_;
				break;
			case '9':
				num[0] = _9_0_;
				num[1] = _9_1_;
				break;
			case 'A': case 'a':
				num[0] = _A_0_;
				num[1] = _A_1_;
				break;
			case 'B': case 'b':
				num[0] = _B_0_;
				num[1] = _B_1_;
				break;
			case 'C': case 'c':
				num[0] = _C_0_;
				num[1] = _C_1_;
				break;
			case 'D': case 'd':
				num[0] = _D_0_;
				num[1] = _D_1_;
				break;
			case 'E': case 'e':
				num[0] = _E_0_;
				num[1] = _E_1_;
				break;
			case 'F': case 'f':
				num[0] = _F_0_;
				num[1] = _F_1_;
				break;
		}
		bc_printbigchar(num, 14, 2 + i * 8 + i, LRED, GREEN);
	}
}

void print_flag()
{
	int flag;
	mt_gotoXY(11, 70);
	sc_regGet(REG_OVERFLOW, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
	
	mt_gotoXY(11, 72);
	sc_regGet(REG_ZERO_DIV, &flag);
	if(flag)
		write(STDOUT_FILENO, "Z ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
		
	mt_gotoXY(11, 74);
	sc_regGet(REG_OVERLIMIT_MEM, &flag);
	if(flag)
		write(STDOUT_FILENO, "L ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
		
	mt_gotoXY(11, 76);
	sc_regGet(REG_STEP_IGNORE, &flag);
	if(flag)
		write(STDOUT_FILENO, "S ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);

	mt_gotoXY(11, 78);
	sc_regGet(REG_WR_COM, &flag);
	if(flag)
		write(STDOUT_FILENO, "W ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
};

void IncInstCount(int signo)
{
	char mem[8];
	int i, j;
	int prev = InstCount;
	int prevx = prev / 10;
	int prevy = prev % 10;
	if(InstCount == 99)
	{
		raise(SIGUSR1);
		return;
	}
	InstCount++;
	int InstCountx = InstCount / 10;
	int InstCounty = InstCount % 10;
	int n;
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	write_ram(prevx, prevy);
	
	mt_setbgcolor(LRED);
	mt_setfgcolor(LWHITE);
	write_ram(InstCountx, InstCounty);
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	mt_gotoXY(5, 70);
	n = sprintf(mem, "%04d", InstCount);
	write(STDOUT_FILENO, mem, n);
	mt_gotoXY(2, 70);
	n = sprintf(mem, "%04X", Accum);
	write(STDOUT_FILENO, mem, n);
	
	big_window(InstCount);
	print_flag();
	
	mt_gotoXY(25, 1);	
	return;
}

void StopIt(int signo)
{
	char mem[8];
	int prev = InstCount - 1;
	struct itimerval nval, oval;
	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 0;
	nval.it_value.tv_sec = 0;
	nval.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &nval, &oval);
	sc_regSet(REG_STEP_IGNORE, 1);
	int i, j, n;
	for(i = 0; i < 10; ++i)
		for(j = 0; j < 10; ++j)
			write_ram(i, j);
	int prevx = prev / 10;
	int prevy = prev % 10;
	int InstCountx = InstCount / 10;
	int InstCounty = InstCount % 10;
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	write_ram(prevx, prevy);
	mt_setbgcolor(LRED);
	mt_setfgcolor(LWHITE);
	write_ram(InstCountx, InstCounty);
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	mt_gotoXY(5, 70);
	n = sprintf(mem, "%04d", InstCount);
	write(STDOUT_FILENO, mem, n);
	mt_gotoXY(2, 70);
	n = sprintf(mem, "%04X", Accum);
	write(STDOUT_FILENO, mem, n);
	
	big_window(InstCount);
	print_flag();
	
	mt_gotoXY(25, 1);
	return;
}

int commandwindow()
{
	enum keys button;
	char buf[] = "                         ";
	char buf1[] = "                           ";
	int yes = 1, retflag = 0;
	mt_setbgcolor(LRED);
	mt_setfgcolor(LWHITE);
	bc_box(3, 15, 6, 26);
	mt_gotoXY(3, 25);
	write(STDOUT_FILENO, "Warning", 7);
	for(int i = 4; i < 9; ++i)
	{
		mt_gotoXY(i, 16);
		write(STDOUT_FILENO, buf, 25);
	}
	mt_gotoXY(4, 17);
	write(STDOUT_FILENO, "Is this an command?", 19);
	while (!(retflag))
	{
		mt_gotoXY(8, 20);
		if(yes)
		{
			mt_setbgcolor(LGREEN);
			write(STDOUT_FILENO, "YES", 3);
			mt_setbgcolor(LRED);
			write(STDOUT_FILENO, "   NO", 5);
		} else {
			mt_setbgcolor(LRED);
			write(STDOUT_FILENO, "YES   ", 6);
			mt_setbgcolor(LGREEN);
			write(STDOUT_FILENO, "NO", 2);
		}
		mt_setbgcolor(LRED);
		mt_gotoXY(25, 1);
		rk_mytermregime(1, 0, 1, 0, 1);
		rk_readkey(&button);
		switch(button)
		{
			case left_key:
			case right_key:
				yes = (yes + 1) % 2;
				break;
			case enter_key:
				retflag = 1;
				break;
			default: break;
		}
	}
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	for(int i = 3; i < 10; ++i)
	{
		mt_gotoXY(i, 15);
		write(STDOUT_FILENO, buf1, 27);
	}
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			write_ram(i, j);
	
	return yes;
}
int write_dex_num(enum keys button, int num[2])
{
	char mem;
	
	switch(button)
	{
		case key_0:
			mem = '0';
			num[0] = _0_0_;
			num[1] = _0_1_;
			break;
		case key_1:
			mem = '1';
			num[0] = _1_0_;
			num[1] = _1_1_;
			break;
		case key_2:
			mem = '2';
			num[0] = _2_0_;
			num[1] = _2_1_;
			break;
		case key_3:
			mem = '3';
			num[0] = _3_0_;
			num[1] = _3_1_;
			break;
		case key_4:
			mem = '4';
			num[0] = _4_0_;
			num[1] = _4_1_;
			break;
		case key_5:
			mem = '5';
			num[0] = _5_0_;
			num[1] = _5_1_;
			break;
		case key_6:
			mem = '6';
			num[0] = _6_0_;
			num[1] = _6_1_;
			break;
		case key_7:
			mem = '7';
			num[0] = _7_0_;
			num[1] = _7_1_;
			break;
		case key_8:
			mem = '8';
			num[0] = _8_0_;
			num[1] = _8_1_;
			break;
		case key_9:
			mem = '9';
			num[0] = _9_0_;
			num[1] = _9_1_;
			break;
		case key_a:
			mem = 'A';
			num[0] = _A_0_;
			num[1] = _A_1_;
			break;
		case key_b:
			mem = 'B';
			num[0] = _B_0_;
			num[1] = _B_1_;
			break;
		case key_c:
			mem = 'C';
			num[0] = _C_0_;
			num[1] = _C_1_;
			break;
		case key_d:
			mem = 'D';
			num[0] = _D_0_;
			num[1] = _D_1_;
			break;
		case key_e:
			mem = 'E';
			num[0] = _E_0_;
			num[1] = _E_1_;
			break;
		case key_f:
			mem = 'F';
			num[0] = _F_0_;
			num[1] = _F_1_;
			break;
		default:
			return -1;
			break;
	}
	write(STDOUT_FILENO, &mem, 1);
	if(mem >= 'A' && mem <= 'F')
		mem = mem - 'A' + 10;
	if(mem >= '0' && mem <= '9')
		mem -= '0';
	return (int)mem;
}

int ALU(int command, int operand)
{
	int buf;
	int a;
	switch(command) {
		case ADD:
			Accum += RAM[operand];
		break;
		case SUB:
			Accum -= RAM[operand];
		break;
		case DIVIDE:
			Accum /= RAM[operand];
		break;
		case MUL:
			Accum *= RAM[operand];
		break;
		case RCR:
			buf = (RAM[operand] & 1) << 14;
			Accum = RAM[operand] / 2;
			Accum += buf;
		break;
		case RCCL:
			a = operand % 15;
			for(int i = 0; i < a; ++i)
			{
				buf = (Accum & (1 << 14)) >> 14;
				Accum = (RAM[operand] & 0x3FFF) * 2;
				Accum += buf;
			}
		break;
	}
	return -1;
}

int CU()
{
	char out[10];
	int value, command, operand, n, i;
	char in[200];
	int num[2];
	int res;
	enum keys inbut;
	sc_memoryGet(InstCount, &value);
	if(sc_commandDecode(value, &command, &operand) != 0)
	{
		sc_regSet(REG_WR_COM, 1);
		raise(SIGUSR1);
		return -1;
	}
	
	if(command >= ADD && command <= MUL || command == RCR || command == RCCL)
		return ALU(command, operand);
	else
	{
		if(command == READ)
		{
			mt_gotoXY(23, 7);
			read(STDIN_FILENO, in, 4);
			
		}
		
		if(command == WRITE)
		{
			n = sprintf(out, "%X", RAM[operand]);
			mt_gotoXY(24, 8);
			write(STDOUT_FILENO, out, n);
		}
		
		if(command == LOAD)
		{
			Accum = RAM[operand];
			return 0;
		}
		
		if(command == STORE)
		{
			RAM[operand] = Accum;
			return 0;
		}
		
		if(command == JUMP)
		{
			if(operand >= 0 && operand <= 99)
			{
				InstCount = operand;
				return 0;
			} else
				return -1;
		}
		
		if(command == JNEG)
		{
			if(operand >= 0 && operand <= 99)
			{
				if(Accum < 0)
					InstCount = operand;
				return 0;
			} else
				return -1;
		}
		
		if(command == JZ)
		{
			if(operand >= 0 && operand <= 99)
			{
				if(Accum == 0)
					InstCount = operand;
				return 0;
			} else
				return -1;
		}
		
		if(command == HALT)
		{
			raise(SIGUSR1);
			return 0;
		}
	}
	return -1;
}


void initialize()
{
	mt_clrscr();
	sc_memoryInit();
	sc_regInit();
	sc_regSet(REG_STEP_IGNORE, 1);		
	memory_window();
	accumulator_window();
	instCount_window();
	operation_window();
	flags_window();
	keys_window();
	bc_box(13, 1, 9, 45);
	IOterminal();
}

void memory_window()
{
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			write_ram(i, j);
	bc_box(1, 1, 11, 60);
	mt_gotoXY(1, 30);
	write(STDOUT_FILENO, " Memory ", 8);
}

void accumulator_window()
{
	char mem[8];
	bc_box(1, 62, 2, 18);
	mt_gotoXY(1, 66);
	write(STDOUT_FILENO, "Accumulator", 11);
	mt_gotoXY(2, 70);
	int n = sprintf(mem, "%04d", Accum);
	write(STDOUT_FILENO, mem, n);
}

void instCount_window()
{
	bc_box(4, 62, 2, 18);
	mt_gotoXY(4, 63);
	write(STDOUT_FILENO, "InstructionCount ", 17);
}
	
void operation_window()
{
	bc_box(7, 62, 2, 18);
	mt_gotoXY(7, 66);
	write(STDOUT_FILENO, "Operation", 9);
}	

void flags_window()
{
	bc_box(10, 62, 2, 18);
	mt_gotoXY(10, 66);
	write(STDOUT_FILENO, "Flags", 5);
}

void keys_window()
{
	bc_box(13, 47, 9, 33);
	mt_gotoXY(13, 48);
	write(STDOUT_FILENO, " Keys ", 6);
	mt_gotoXY(14, 48);
	write(STDOUT_FILENO, "L  - Load", 9);
	mt_gotoXY(15, 48);
	write(STDOUT_FILENO, "S  - Save", 9);
	mt_gotoXY(16, 48);
	write(STDOUT_FILENO, "R  - Run", 8);
	mt_gotoXY(17, 48);
	write(STDOUT_FILENO, "T  - Step", 9);
	mt_gotoXY(18, 48);
	write(STDOUT_FILENO, "I  - Reset", 10);
	mt_gotoXY(19, 48);
	write(STDOUT_FILENO, "F5 - Accumulator", 16);
	mt_gotoXY(20, 48);
	write(STDOUT_FILENO, "F6 - InstructionCounter", 23);
}

void print_value(int prev)
{
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			write_ram(i, j);
	int prevx = prev / 10;
	int prevy = prev % 10;
	int InstCountx = InstCount / 10;
	int InstCounty = InstCount % 10;
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	write_ram(prevx, prevy);
	mt_setbgcolor(LRED);
	mt_setfgcolor(LWHITE);
	write_ram(InstCountx, InstCounty);
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
	
}

void set_Accum()
{
	mt_gotoXY(2, 70);
	for(int i = 1; i < 5; ++i)
	{
		enum keys subbut;
		rk_readkey(&subbut);
		
		char mem;
		
		switch(subbut)
		{
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
				if(i == 1)
				{
					i--;
					break;
				}
				mem = '8';
				write(STDOUT_FILENO, &mem, 1);
				mem = 8;
				break;
			case key_9:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = '9';
				write(STDOUT_FILENO, &mem, 1);
				mem = 9;
				break;
			case key_a:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'A';
				write(STDOUT_FILENO, &mem, 1);
				mem = 10;
				break;
			case key_b:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'B';
				write(STDOUT_FILENO, &mem, 1);
				mem = 11;
				break;
			case key_c:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'C';
				write(STDOUT_FILENO, &mem, 1);
				mem = 12;
				break;
			case key_d:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'D';
				write(STDOUT_FILENO, &mem, 1);
				mem = 13;
				break;
			case key_e:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'E';
				write(STDOUT_FILENO, &mem, 1);
				mem = 14;
				break;
			case key_f:
				if(i == 1)
				{
					i--;
					break;
				}
				mem = 'F';
				write(STDOUT_FILENO, &mem, 1);
				mem = 15;
				break;
			default: 
				--i;
				continue;
				break;
		}
		Accum <<= 4;
		Accum += mem;
	}
}

void set_InstCount()
{
	char buf[3];
	mt_gotoXY(5, 70);
	write(STDOUT_FILENO, "    ", 4);
	mt_gotoXY(5, 70);
	rk_mytermregime(1, 0, 2, 1, 1);
	read(STDIN_FILENO, buf, 2);
	int need = (buf[0]-'0') * 10 + (buf[1]-'0');
	if(need <= 99 && need >= 0)
		InstCount = need;
}

void refresh()
{
	raise(SIGUSR1);
	sc_memoryInit();
	sc_regInit();
	Accum = 0;
	sc_regSet(REG_STEP_IGNORE, 1);
}

void enter_ram()
{
	int flag = commandwindow();
	int wr = 0;
	int com = 0, oper = 0;
	int mem;
	int num[2];
	
	int InstCountx = InstCount / 10;
	int InstCounty = InstCount % 10;
	
	for(int i = 1; i < 5; ++i)
	{
		mt_gotoXY(InstCountx + 2, InstCounty * 6 + 2 + i);
		rk_mytermregime(1, 0, 1, 0, 1);
		enum keys subbut;
		rk_readkey(&subbut);
		mem = write_dex_num(subbut, num);
		if(mem == -1)
		{
			i--;
			continue;
		}
		if(!flag)
		{
			wr <<= 4;
			wr += mem;
		}
		else
		{
			if(i <= 2)
			{
				com <<= 4;
				com += mem;
			} else {
				oper <<= 4;
				oper += mem;
			}
		}
		bc_printbigchar(num, 14, 2 + i * 8 + i, LRED, GREEN);
	}
	if(flag)
	{
		int enc = sc_commandEncode(com, oper, &wr);
		if(enc != 0)
		{
			wr = 0;
			wr += com;
			wr <<= 4;
			wr += oper;
			wr |= 0x1 << 14;
		}
	}
	else 
	{
		if(wr > 0x3FFF)
			wr = 0x3FFF;
		wr |= 0x1 << 14;
	}
	sc_memorySet(InstCount, wr);
}

void operation()
{
	char mem[10];
	int com = 0, oper = 0, n;
	int value = 0;
	int flag, flagprev;
	
	mt_gotoXY(8, 66);
	sc_regGet(REG_WR_COM, &flagprev);
	sc_memoryGet(InstCount, &value);
	flag = sc_commandDecode(value, &com, &oper);
	if(flag == 0)
	{
		n = sprintf(mem, "+%02X : %02X", com, oper);
		write(STDOUT_FILENO, mem, n);
	}
	else
	{
		write(STDOUT_FILENO, "+00 : 00", 8);
	}
	sc_regSet(REG_WR_COM, flagprev);
}

void IOterminal()
{
	mt_gotoXY(23, 1);
	write(STDOUT_FILENO, "Input:               \nOutput:               ", 44);
}