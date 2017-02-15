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

#include "sc.c"
#include <stdio.h>

void showMemory()
{
	int i, j;
	for(i = 0; i < 10; ++i)
	{
		for(j = 0; j < 10; ++j)
			printf("%4d ", RAM[i*10 + j]);
		printf("\n");
	}
};

int main(int argc, char **argv)
{
	int i, j;
	int code;
	
	code = sc_memoryInit();
	printf("sc_memoryInit() = %1d\n", code);
	showMemory();
	
	code = sc_regInit();
	printf("sc_regInit() = %1d\n", code);
	printf("%8p (flags - 5 bits of last byte)\n", REG);
	
	code = sc_memorySet(23, 10);
	printf("\nsc_memorySet(23, 10) = %1d\n", code);
	showMemory();
	
	code = sc_memorySet(101, 10);
	printf("\nsc_memorySet(101, 10) = %1d\n", code);
	showMemory();
	
	int val;
	code = sc_memoryGet(23, &val);
	printf("\nsc_memoryGet(23, &val) = %1d\n", code);
	printf("int val = %3d\n", val);
	
	code = sc_memoryGet(200, &val);
	printf("\nsc_memoryGet(200, &val) = %1d\n", code);
	printf("int val = %3d\n", val);
	
	
	return 0;
}

