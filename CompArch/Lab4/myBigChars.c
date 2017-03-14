
#include <stdio.h>
#include "myTerm.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

int bc_printA (char * str)
{
	write(1, "\e(0", 3);
	int n = strlen(str);
	write(1, str, n);
	write(1, "\e(B", 3);
}
int bc_box(int x1, int y1, int x2, int y2)
{
	write(1, "\e(0", 3);
	int err = mt_gotoXY(x1, y1);
	if(err < 0)
		return -1;
	write(1, "l", 1);
	int i;
	for(i = 1; i < y2; ++i)
	{
		mt_gotoXY(x1, y1 + i);
		write(1, "q", 1);
	}
	write(1, "k", 1);
	mt_gotoXY(x1 + x2, y1);
	write(1, "m", 1);
	for(i = 1; i < y2; ++i)
	{
		mt_gotoXY(x1 + x2, y1 + i);
		write(1, "q", 1);
	}
	write(1, "j", 1);
	for(i = 1; i < x2; ++i)
	{
		mt_gotoXY(x1 + i, y1);
		write(1, "x", 1);
		mt_gotoXY(x1 + i, y1 + y2);
		write(1, "x", 1);
	}
	write(1, "\e(B", 3);
	return 0;
}

int bc_printbigchar (int num[2], int x, int y, enum colors fg, enum colors bg)
{
	write(1, "\e(0", 3);
	mt_setbgcolor(bg);
	mt_setfgcolor(fg);
	mt_gotoXY(x, y);
	int i, j;
	for(i = 0; i < 8; ++i)
	{
		int k = i * 8;
		int numarr = 0;
		if(i >= 4) 
		{
			++numarr;
			k = (i-4) * 8;
		}
		mt_gotoXY(x + i, y);
		for(j = 0; j < 8; ++j)
		{
			if(((num[numarr] >> (k + j)) % 2 == 0))
				write(1, " ", 1);
			else
				write(1, "a", 1);
		}
	}
	write(1, "\e(B", 3);
	return 0;
}
int bc_setbigcharpos (int * big, int x, int y, int value)
{
	int numbig = 0;
	int k = y;
	int byte = x * 8;
	if(x >= 4) 
	{
		++numbig;
		byte = (x-4) * 8;
	}
	if(value)
		big[numbig] |= (1 << (byte + k));
	else
		big[numbig] &= ~(1 << (byte + k));
	return 0;
}
int bc_getbigcharpos(int * big, int x, int y, int *value)
{
	int numbig = 0;
	int k = y;
	int byte = x * 8;
	if(x >= 4) 
	{
		++numbig;
		byte = (x-4) * 8;
	}
	*value = (big[numbig] >> (byte + k)) & 0x1;
	return 0;
}
int bc_bigcharwrite (int fd, int * big, int count)
{
	char alph[8][8];
	int buf;
	int i, j;
	for(i = 0; i < 8; ++i)
	{
		int numbig = 0;
		int byte = i * 8;
		if(i >= 4) 
		{
			++numbig;
			byte = (i-4) * 8;
		}
		for(j = 0; j < 8; ++j)
		{
			buf = (big[numbig] >> (byte + j)) & 0x1;
			if(!buf)
				write(fd, " ", 1);
			else
				write(fd, "a", 1);
		}
	}
	return 0;
}
int bc_bigcharread (int fd, int * big, int need_count, int * count)
{
	char buf[32];
	int countbuf;
	for(int i = 0; i < (need_count * 2); ++i)
	{
		big[i] = 0;
		countbuf = read(fd, buf, 32);
		if(countbuf < 0)
		{
			*count = 0;
			return -1;
		}
		*count += 1;
		for(int j = 31; j >= 0; --j)
		{
			big[i] <<= 1;
			if(buf[j] == 'a')
			{
				big[i] += 1;
			}
		}
	}
	return 0;
}

int main()
{
	
	bc_box(1,1,9,9);
	int a[2] = {0x181C1810, 0x3c181818};
	bc_printbigchar(a, 2, 2, YELLOW, WHITE);
	int value;
	bc_getbigcharpos(a, 0, 4, &value);
	int fd = open("ara.txt", O_WRONLY);
	bc_bigcharwrite(fd, a, 1);
	int count = 0;
	close(fd);
	fd = open("ara.txt", O_RDONLY);
	bc_bigcharread(fd, a, 1, &count);
	bc_printbigchar(a, 12, 22, YELLOW, WHITE);
	close(fd);
	return 0;
}
