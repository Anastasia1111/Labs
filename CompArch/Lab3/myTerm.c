#include "myTerm.h"

int mt_clrscr (void)
{
	
}

int mt_gotoXY (int, int)
{
	
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

int mt_setfgcolor (enum colors)
{
	
}

int mt_setbgcolor (enum colors)
{
	
}
