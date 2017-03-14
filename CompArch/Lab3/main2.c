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
#include "myTerm.h"
#include "sc.h"

int main(int argc, char **argv)
{
	int i, j;
	int value = 0;
	mt_clrscr();
	write(STDOUT_FILENO, "\e(0", 4);
	
	mt_setbgcolor(LGREEN);
	mt_setfgcolor(GREEN);
	
	//memory_window
	
	mt_gotoXY(1, 1);
	write(STDOUT_FILENO, "lqqqqqqqqqqqqqqqqqqqqqqqqqqqq MEMORY qqqqqqqqqqqqqqqqqqqqqqqk", 61);
	for(i = 0; i < 10; ++i)
	{
		mt_gotoXY(i+2, 1);
		write(STDOUT_FILENO, "x", 1);
		for(j = 0; j < 10; ++j)
		{
			sc_memoryGet(i * 10 + j, &value);
			write(STDOUT_FILENO, "+0000 ", 6);
		}
		write(STDOUT_FILENO, "\bx", 2);
	}
	mt_gotoXY(12, 1);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj", 61);
	
	// accumulator_window
	
	mt_gotoXY(1, 62);
	write(STDOUT_FILENO, "lqqq ACCUMULATOR qqqqk", 22);
	mt_gotoXY(2, 62);
	write(STDOUT_FILENO, "x       +0000        x", 22);
	mt_gotoXY(3, 62);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqj", 22);
	
	//instCount_window
	
	mt_gotoXY(4, 62);
	write(STDOUT_FILENO, "l INSTRUCTIONCOUNTER k", 22);
	mt_gotoXY(5, 62);
	write(STDOUT_FILENO, "x       +0000        x", 22);
	mt_gotoXY(6, 62);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqj", 22);
	
	//Operation_window
	
	mt_gotoXY(7, 62);
	write(STDOUT_FILENO, "lqqqqq OPERATION qqqqk", 22);
	mt_gotoXY(8, 62);
	write(STDOUT_FILENO, "x      +00 : 00      x", 22);
	mt_gotoXY(9, 62);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqj", 22);
	
	//Flags_window
	
	mt_gotoXY(10, 62);
	write(STDOUT_FILENO, "lqqqqq FLAGS qqqqqqqqk", 22);
	mt_gotoXY(11, 62);
	write(STDOUT_FILENO, "x     ", 6);
	
	int flag;
	sc_regGet(REG_OVERFLOW, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "  ", 2);
	sc_regGet(REG_ZERO_DIV, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "  ", 2);
	sc_regGet(REG_OVERLIMIT_MEM, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "  ", 2);
	sc_regGet(REG_STEP_IGNORE, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "  ", 2);
	sc_regGet(REG_WR_COM, &flag);
	if(flag)
		write(STDOUT_FILENO, "O ", 2);
	else
		write(STDOUT_FILENO, "  ", 2);
	
	write(STDOUT_FILENO, "     x", 6);
	mt_gotoXY(12, 62);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqj", 22);
	
	//KEYS_window
	
	mt_gotoXY(13, 47);
	write(STDOUT_FILENO, "l KEYS qqqqqqqqqqqqqqqqqqqqqqqqqqqqqk", 37);
	mt_gotoXY(14, 47);
	write(STDOUT_FILENO, "xL  - LOAD                          x", 37);
	mt_gotoXY(15, 47);
	write(STDOUT_FILENO, "xS  - SAVE                          x", 37);
	mt_gotoXY(16, 47);
	write(STDOUT_FILENO, "xR  - RUN                           x", 37);
	mt_gotoXY(17, 47);
	write(STDOUT_FILENO, "xT  - STEP                          x", 37);
	mt_gotoXY(18, 47);
	write(STDOUT_FILENO, "xI  - RESET                         x", 37);
	mt_gotoXY(19, 47);
	write(STDOUT_FILENO, "xF5 - ACCUMULATOR                   x", 37);
	mt_gotoXY(20, 47);
	write(STDOUT_FILENO, "xF6 - INSTRUCTIONCOUNTER            x", 37);
	mt_gotoXY(21, 47);
	write(STDOUT_FILENO, "x                                   x", 37);
	mt_gotoXY(22, 47);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj", 37);
	
	//BIG_window
	
	mt_gotoXY(13, 1);
	write(STDOUT_FILENO, "lqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqk", 46);
	for(i = 14; i < 22; ++i)
	{
		mt_gotoXY(i, 1);
		write(STDOUT_FILENO, "x                                            x", 46);
	}
	mt_gotoXY(22, 1);
	write(STDOUT_FILENO, "mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj", 46);
	
	mt_gotoXY(23, 1);
	write(STDOUT_FILENO, "\e(B", 3);
	return 0;
}
