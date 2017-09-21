#include "myBigChars.h"

int bc_printA (char * str)
{
	write(1, "\e(0", 3);
	int n = strlen(str);
	write(1, str, n);
	write(1, "\e(B", 3);
	return 0;
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
	mt_setbgcolor(DEF);
	mt_setfgcolor(DEF);
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
