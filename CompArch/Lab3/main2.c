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
	printf("\e(0");
	
	mt_setbgcolor(LGREEN);
	mt_setfgcolor(GREEN);
	
	//memory_window
	
	mt_gotoXY(1, 1);
	printf("lqqqqqqqqqqqqqqqqqqqqqqqqqqqq MEMORY qqqqqqqqqqqqqqqqqqqqqqqk");
	for(i = 0; i < 10; ++i)
	{
		mt_gotoXY(i+2, 1);
		printf("x");
		for(j = 0; j < 10; ++j)
		{
			sc_memoryGet(i * 10 + j, &value);
			printf("+%04X ", value);
		}
		printf("\bx");
	}
	mt_gotoXY(12, 1);
	printf("mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj");
	
	// accumulator_window
	
	mt_gotoXY(1, 62);
	printf("lqqq ACCUMULATOR qqqqk");
	mt_gotoXY(2, 62);
	printf("x       +0000        x\n");
	mt_gotoXY(3, 62);
	printf("mqqqqqqqqqqqqqqqqqqqqj");
	
	//instCount_window
	
	mt_gotoXY(4, 62);
	printf("l INSTRUCTIONCOUNTER k");
	mt_gotoXY(5, 62);
	printf("x       +0000        x\n");
	mt_gotoXY(6, 62);
	printf("mqqqqqqqqqqqqqqqqqqqqj");
	
	//Operation_window
	
	mt_gotoXY(7, 62);
	printf("lqqqqq OPERATION qqqqk");
	mt_gotoXY(8, 62);
	printf("x      +00 : 00      x\n");
	mt_gotoXY(9, 62);
	printf("mqqqqqqqqqqqqqqqqqqqqj");
	
	//Flags_window
	
	mt_gotoXY(10, 62);
	printf("lqqqqq FLAGS qqqqqqqqk");
	mt_gotoXY(11, 62);
	printf("x     ");
	
	int flag;
	sc_regGet(REG_OVERFLOW, &flag);
	if(flag)
		printf("O ");
	else
		printf("  ");
	sc_regGet(REG_ZERO_DIV, &flag);
	if(flag)
		printf("O ");
	else
		printf("  ");
	sc_regGet(REG_OVERLIMIT_MEM, &flag);
	if(flag)
		printf("O ");
	else
		printf("  ");
	sc_regGet(REG_STEP_IGNORE, &flag);
	if(flag)
		printf("O ");
	else
		printf("  ");
	sc_regGet(REG_WR_COM, &flag);
	if(flag)
		printf("O ");
	else
		printf("  ");
	
	printf("     x\n");
	mt_gotoXY(12, 62);
	printf("mqqqqqqqqqqqqqqqqqqqqj");
	
	//KEYS_window
	
	mt_gotoXY(13, 47);
	printf("l KEYS qqqqqqqqqqqqqqqqqqqqqqqqqqqqqk");
	mt_gotoXY(14, 47);
	printf("xL  - LOAD                          x");
	mt_gotoXY(15, 47);
	printf("xS  - SAVE                          x");
	mt_gotoXY(16, 47);
	printf("xR  - RUN                           x");
	mt_gotoXY(17, 47);
	printf("xT  - STEP                          x");
	mt_gotoXY(18, 47);
	printf("xI  - RESET                         x");
	mt_gotoXY(19, 47);
	printf("xF5 - ACCUMULATOR                   x");
	mt_gotoXY(20, 47);
	printf("xF6 - INSTRUCTIONCOUNTER            x");
	mt_gotoXY(21, 47);
	printf("x                                   x");
	mt_gotoXY(22, 47);
	printf("mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj");
	
	//BIG_window
	
	mt_gotoXY(13, 1);
	printf("lqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqk");
	for(i = 14; i < 22; ++i)
	{
		mt_gotoXY(i, 1);
		printf("x                                            x");
	}
	mt_gotoXY(22, 1);
	printf("mqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqj");
	
	mt_gotoXY(23, 1);
	printf("\e(B");
	return 0;
}
