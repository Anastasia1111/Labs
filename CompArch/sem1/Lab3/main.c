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

int main(int argc, char **argv)
{
	int a, b;
	mt_clrscr();
	mt_gotoXY(5, 5);
	mt_getscreensize (&a, &b);
	
	mt_setbgcolor(LWHITE);
	mt_setfgcolor(YELLOW);
	printf("rows - %d \n", a);
	mt_setbgcolor(RED);
	mt_setfgcolor(LGREEN);
	printf("cols - %d ", b);
	/*mt_gotoXY(1, 2);
	mt_setbgcolor(PURPLE);
	mt_setfgcolor(LWHITE);
	
	int value = 0;
	value = mt_setbgcolor(999);
	printf("value = mt_setbgcolor(999) = %d;\n", value);
	value = mt_setfgcolor(999);
	printf("value = mt_setfgcolor(999) = %d;\n", value);
	*/
	return 0;
}
