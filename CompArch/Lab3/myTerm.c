#include "myTerm.h"

int mt_clrscr (void)
{
	write(1, "\e[H\e[2J", 7);
	return 0;
}

int mt_gotoXY (int x, int y)
{
	char cmd[10];
	int num = sprintf(cmd, "\e[%03d;%03dH", x, y);
	write(1, cmd, num);
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
	for(buf = GRAY; buf <= BLACK; ++buf)
	{
		if(color == buf)
		{
			errflag = 0;
			break;
		}
	}
	if(errflag)
		return -1;
	char cmd[10];
	int num = sprintf(cmd, "\e[38;5;%02dm", color);
		write(1, cmd, num);
	return 0;
}

int mt_setbgcolor (enum colors color)
{
	enum colors buf;
	int errflag = 1;
	for(buf = GRAY; buf <= BLACK; ++buf)
	{
		if(color == buf)
		{
			errflag = 0;
			break;
		}
	}
	if(errflag)
		return -1;
	char cmd[10];
	int num = sprintf(cmd, "\e[48;5;%02dm", color);
		write(1, cmd, num);
	return 0;
}
