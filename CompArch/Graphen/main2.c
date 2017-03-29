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

int main(int argc, char **argv)
{
	int i, j;
	int a = 38;
	int value = 0, flag;
	mt_clrscr();
	char mem[6];
	int n;
	sc_memoryInit();
	sc_memorySet(a,0x50F);
	//memory_window
	
	int com, oper;
	for(i = 0; i < 10; ++i)
	{
		mt_gotoXY(i+2, 2);
		for(j = 0; j < 10; ++j)
		{
			int flag1;
			sc_regGet(REG_WR_COM, &flag1);
			sc_memoryGet((i+1) * 10 + (j+1), &value);
			flag = sc_commandDecode(value, &com, &oper);
			if(flag == 0)
			{
				n = sprintf(mem, "+%02X%02X ", com, oper);
				write(STDOUT_FILENO, mem, n);
			}
			else
			{
				n = sprintf(mem, " %04X ", value);
				write(STDOUT_FILENO, mem, n);
				if(!flag1)
					sc_regSet(REG_WR_COM, 0);
			}
		}
	}
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
	mt_gotoXY(5, 70);
	n = sprintf(mem, "%04d", a);
	write(STDOUT_FILENO, mem, n);
	
	//Operation_window
	
	bc_box(7, 62, 2, 18);
	mt_gotoXY(7, 66);
	write(STDOUT_FILENO, "Operation", 9);
	
	//Flags_window
	
	bc_box(10, 62, 2, 18);
	mt_gotoXY(10, 66);
	write(STDOUT_FILENO, "Flags", 5);
	
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
	mt_gotoXY(14, 2);
	sc_memoryGet(a, &value);
	flag = sc_commandDecode(value, &com, &oper);
	if(!flag)
	{
		n = sprintf(mem, "+%02X%02X ", com, oper);
	}
	else
	{
		n = sprintf(mem, " %04X ", value);
		sc_regSet(REG_WR_COM, 0);
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
	mt_gotoXY(25, 1);
	return 0;
}
