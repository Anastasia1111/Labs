#include "myTerm.h"

int mt_clrscr (void)
{
	/*int fd;
	fd = open ("/dev/tty1", O_WRONLY);
	if (fd == -1)
	{
		fprintf (stderr, "Ошибка открытия терминала.\n");
		return -1;
	}
	write (fd, clear, 9);
	close (fd);*/
	printf("\e[H\e[2J");
	return 0;
}

int mt_gotoXY (int x, int y)
{
	printf("\e[%d;%dH", x, y);
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
	printf("\e[%dm", color);
	return 0;
}

int mt_setbgcolor (enum colors color)
{
	printf("\e[%dm", (color + 10));
	return 0;
}