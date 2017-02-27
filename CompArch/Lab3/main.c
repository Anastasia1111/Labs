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
	mt_getscreensize (&a, &b);
	mt_gotoXY(16, 22);
	mt_setbgcolor(WHITE);
	mt_setfgcolor(YELLOW);
	printf("rows - %d", a);
	mt_setfgcolor(GREEN);
	printf("cols - %d", b);
	return 0;
}
