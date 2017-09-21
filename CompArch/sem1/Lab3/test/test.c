/*
 * test.c
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


#include <stdio.h>

enum colors {GRAY = 0, RED, GREEN, YELLOW, BLUE, PURPLE, TURQUO, WHITE,
	LGRAY, LRED, LGREEN, LYELLOW, LBLUE, LPURPLE, LTURQUO, LWHITE, BLACK};


int main(int argc, char **argv)
{
	int j = 0;
	for(int color = 0; color < 256; ++color)
	{
		printf("\e[48;5;%dm   ", color);
		//printf("%3d ", color);
		++j;
		if(j >= 16)
		{
			j = 0;
			printf("\n");
		}
	}
	return 0;
}

