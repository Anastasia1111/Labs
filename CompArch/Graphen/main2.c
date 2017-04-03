/*
 * main.c
 * 
 * Copyright 2017 Monstruos <monstruos@monstruos-X550MJ>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdlib.h>
#include "myBigChars.h"
#include "sc.h"
#include "myReadKey.h"


void write_ram(int x, int y);
void big_window(int curr);
void print_flag();

int main(int argc, char **argv)
{
	int i, j;
	int curr = 0;
	int value = 0, flag;
	mt_clrscr();
	char mem[6];
	int n;
	sc_memoryInit();
	
	//memory_window
	
	int com, oper;
	for(i = 0; i < 10; ++i)
		for(j = 0; j < 10; ++j)
			write_ram(i, j);
	bc_box(1, 1, 11, 60);
	mt_gotoXY(1, 30);
	write(STDOUT_FILENO, " Memory ", 8);
	
	
	// accumulator_window
	
	bc_box(1, 62, 2, 18);
	mt_gotoXY(1, 66);
	write(STDOUT_FILENO, "Accumulator", 11);
	
	//instCount_window
	
	bc_box(4, 62, 2, 18);
	mt_gotoXY(4, 63);
	write(STDOUT_FILENO, "InstructionCount ", 17);
	
	//Operation_window
	
	bc_box(7, 62, 2, 18);
	mt_gotoXY(7, 66);
	write(STDOUT_FILENO, "Operation", 9);
	
	//Flags_window
	
	bc_box(10, 62, 2, 18);
	mt_gotoXY(10, 66);
	write(STDOUT_FILENO, "Flags", 5);
	
	//KEYS_window
	
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
	
	//BIG_window
	
	bc_box(13, 1, 9, 45);
	
	//MECHANISM
	int prev = curr;
	int prevx, prevy, currx, curry;
	
	enum keys button;
	while(1)
	{
		prevx = prev / 10;
		prevy = prev % 10;
		currx = curr / 10;
		curry = curr % 10;
		
		mt_setbgcolor(DEF);
		mt_setfgcolor(DEF);
		write_ram(prevx, prevy);
		
		mt_setbgcolor(LRED);
		mt_setfgcolor(LWHITE);
		write_ram(currx, curry);
		mt_setbgcolor(DEF);
		mt_setfgcolor(DEF);
		mt_gotoXY(5, 70);
		n = sprintf(mem, "%04d", curr);
		write(STDOUT_FILENO, mem, n);
		
		big_window(curr);
		print_flag();
		
		rk_mytermregime(1, 0, 1, 0, 1);
		rk_readkey(&button);
		
		prev = curr;
		
		switch(button)
		{
			case l_key:
				sc_memoryLoad("RAMsave.txt");
				for(i = 0; i < 10; ++i)
					for(j = 0; j < 10; ++j)
						write_ram(i, j);
				break;
			case s_key:
				sc_memorySave("RAMsave.txt");
				break;
			case r_key:
				
				break;
			case t_key:
				break;
			case i_key:
				break;
			case f5_key:
			{
				char buf[5];
				mt_gotoXY(2, 70);
				write(STDOUT_FILENO, "     ", 5);
				mt_gotoXY(2, 70);
				rk_mytermregime(1, 0, 4, 1, 1);
				read(STDIN_FILENO, buf, 4);
				int need[4] = {-1, -1, -1, -1};
				int alarm = 0;
				for(i = 0; i < 4; ++i)
				{
					if(buf[i] >= '0' && buf[i] <= '9')
						need[i] = buf[i]-'0';
					if(buf[i] >= 'a' && buf[i] <= 'f')
						need[i] = buf[i]-'a' + 10;
					if(buf[i] >= 'A' && buf[i] <= 'F')
						need[i] = buf[i]-'A' + 10;
					if(need[i] < 0)
						alarm = 1;
				}
				if(!alarm)
				{
					int com = need[0]*0x10 + need[1];
					int val = need[2]*0x10 + need[3];
					//sc_com
					//sc_memorySet(curr, 
				}
				break;
			}
			case f6_key:
			{
				char buf[3];
				mt_gotoXY(5, 70);
				write(STDOUT_FILENO, "    ", 4);
				mt_gotoXY(5, 70);
				rk_mytermregime(1, 0, 2, 1, 1);
				read(STDIN_FILENO, buf, 2);
				int need = (buf[0]-'0') * 10 + (buf[1]-'0');
				if(need <= 99 && need >= 0)
					curr = need;
				break;
			}
			case enter_key:
				break;
			case up_key:
				if((curr - 10) >= 0)
					curr -= 10;
				break;
			case down_key:
				if((curr + 10) <= 99)
					curr += 10;
				break;
			case left_key:
				if((curr - 1) >= 0)
					curr--;
				break;
			case right_key:
				if((curr + 1) <= 99)
					curr++;
				break;
			case quit_key:
				break;
			default:
				rk_mytermregime(0, 0, 1, 1, 1);
				break;
		}
		rk_mytermregime(1, 0, 1, 0, 1);
	}
	
	return 0;
}

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
		n = sprintf(mem, " %04X", value);
		write(STDOUT_FILENO, mem, n);
		sc_regSet(REG_WR_COM, flagprev);
	}
};

void big_window(int curr)
{
	mt_gotoXY(14, 2);
	char mem[6];
	int com, oper, n, i, j;
	int value = 0;
	int flag, flagprev;
	
	sc_memoryGet(curr, &value);
	sc_regGet(REG_WR_COM, &flagprev);
	flag = sc_commandDecode(value, &com, &oper);
	if(!flag)
		n = sprintf(mem, "+%02X%02X ", com, oper);
	else
	{
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
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
		
	mt_gotoXY(11, 74);
	sc_regGet(REG_OVERLIMIT_MEM, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
		
	mt_gotoXY(11, 76);
	sc_regGet(REG_STEP_IGNORE, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);

	mt_gotoXY(11, 78);
	sc_regGet(REG_WR_COM, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "_ ", 2);
};
