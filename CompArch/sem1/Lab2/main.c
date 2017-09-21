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

int main(int argc, char **argv)
{
	int i, j;
	int code;
	
	code = sc_memoryInit();
	printf("sc_memoryInit() = %1d\n", code);
	
	code = sc_memorySet(23, 10);
	printf("\nsc_memorySet(23, 10) = %1d\n", code);
	
	for(int i = 0; i < 30; ++i)
		sc_memorySet(rand() % 100, rand() % 10000);
	
	code = sc_memorySet(101, 10);
	printf("sc_memorySet(101, 10) = %1d\n", code);
	
	code = sc_memorySave("RAMsave.txt");
	printf("sc_memorySave('RAMsave.txt') = %1d\n", code);
	
	code = sc_memoryInit();
	printf("sc_memoryInit() = %1d\n", code);
	
	code = sc_memoryLoad("RAMsave.txt");
	printf("sc_memoryLoad('RAMsave.txt') = %1d\n", code);
	
	int val;
	code = sc_memoryGet(23, &val);
	printf("\nsc_memoryGet(23, &val) = %1d\n", code);
	printf("int val = %3d\n", val);
	
	code = sc_memoryGet(200, &val);
	printf("sc_memoryGet(200, &val) = %1d\n", code);
	printf("int val = %3d (shouldn't be changed)\n", val);
	
	code = sc_regInit();
	printf("\nsc_regInit() = %1d\n", code);
	
	printf("\n**sc_memorySet(101, 10) change the flag with code 3 (overloading memory)\n");
	
	code = sc_regGet(3, &val);
	printf("sc_regGet(3, &val) = %1d\n", code);
	printf("int val = %3d\n", val);
	
	code = sc_regSet(REG_OVERLIMIT_MEM, 0);
	printf("sc_regSet(3, 0) = %1d\n", code);
	
	code = sc_regGet(REG_OVERLIMIT_MEM, &val);
	printf("sc_regGet(3, &val) = %1d\n", code);
	printf("int val = %3d\n", val);
	
	code = sc_commandEncode (32, 32, &val);
	printf("\nsc_commanEncode (32, 32, &val) = %1d\n", code);
	printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
	
	code = sc_commandEncode (12, 32, &val);
	printf("\nsc_commanEncode (12, 32, &val) = %1d\n", code);
	printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
	
	code = sc_commandEncode (32, 1000, &val);
	printf("\nsc_commanEncode (32, 1000, &val) = %1d\n", code);
	printf("int val = %6d(should be 4128 = '0 0100000 0100000')\n", val);
	
	int cmd = 0, oper = 0;
	code = sc_commandDecode (val, &cmd, &oper);
	printf("\nsc_commandDecode (val, &cmd, &oper) = %1d\n", code);
	printf("int cmd = %2d, int oper = %2d(should be 32; 32)\n", cmd, oper);
	
	return 0;
}

