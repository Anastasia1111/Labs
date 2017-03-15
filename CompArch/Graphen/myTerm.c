#include "myTerm.h"

int mt_clrscr (void)
{
	write(STDOUT_FILENO, "\e[H\e[2J", 7);
	return 0;
}

int mt_gotoXY (int x, int y)
{
	char cmd[10];
	int i = 0;
	cmd[i++] = '\e';
	cmd[i++] = '[';
	if(x >= 100)
		cmd[i++] = x / 100 + '0';
	if(x >= 10)
		cmd[i++] = ((x / 10) % 10) + '0';
	cmd[i++] = x % 10 + '0';
	cmd[i++] = ';';
	if(y >= 100)
		cmd[i++] = y / 100 + '0';
	if(y >= 10)
		cmd[i++] = ((y / 10) % 10) + '0';
	cmd[i++] = y % 10 + '0';
	cmd[i++] = 'H';
	write(STDOUT_FILENO, cmd, i);
	return 0;
}

int mt_getscreensize (int * rows, int * cols)
{
	struct winsize trwin;
	if (!ioctl(1, TIOCGWINSZ, &trwin)){
		*rows = trwin.ws_row;
		*cols = trwin.ws_col;
	} else {
		return -1;
	}
	return 0;
}

int mt_setfgcolor (enum colors color)
{
	enum colors buf;
	int errflag = 1;
	for(buf = GRAY; buf <= DEF; ++buf)
	{
		if(color == buf)
		{
			errflag = 0;
			break;
		}
	}
	if(color == DEF)
	{
		write(1, "\e[38;5;m", 8);
		return 0;
	}
	if(errflag)
		return -1;
	char cmd[10];
	int i = 0;
	cmd[i++] = '\e';
	cmd[i++] = '[';
	cmd[i++] = '3';
	cmd[i++] = '8';
	cmd[i++] = ';';
	cmd[i++] = '5';
	cmd[i++] = ';';
	if(color >= 10)
		cmd[i++] = (color / 10) + '0';
	cmd[i++] = color % 10 + '0';
	cmd[i++] = 'm';
	write(STDOUT_FILENO, cmd, i);
	return 0;
}

int mt_setbgcolor (enum colors color)
{
	enum colors buf;
	int errflag = 1;
	for(buf = GRAY; buf <= DEF; ++buf)
	{
		if(color == buf)
		{
			errflag = 0;
			break;
		}
	}
	if(color == DEF)
	{
		write(1, "\e[48;5;m", 8);
		return 0;
	}
	if(errflag)
		return -1;
	char cmd[10];
	int i = 0;
	cmd[i++] = '\e';
	cmd[i++] = '[';
	cmd[i++] = '4';
	cmd[i++] = '8';
	cmd[i++] = ';';
	cmd[i++] = '5';
	cmd[i++] = ';';
	if(color >= 10)
		cmd[i++] = (color / 10) + '0';
	cmd[i++] = color % 10 + '0';
	cmd[i++] = 'm';
	write(STDOUT_FILENO, cmd, i);
	return 0;
}
