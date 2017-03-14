#ifndef MYTERM_H
#define MYTERM_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

enum colors {GRAY = 0, RED = 1, GREEN = 2, YELLOW = 3, BLUE = 4, PURPLE = 5, TURQUO = 6, WHITE = 7,
	LGRAY = 8, LRED = 9, LGREEN = 10, LYELLOW = 11, LBLUE = 12, LPURPLE = 13, LTURQUO = 14, LWHITE = 15, BLACK = 16};

int mt_clrscr (void); //производит очистку и перемещение курсора в левый верхний угол экрана;

int mt_gotoXY (int, int); /*перемещает курсор в указанную позицию. Первый
параметр номер строки, второй - номер столбца;*/

int mt_getscreensize (int * rows, int * cols); /*определяет размер экрана
терминала (количество строк и столбцов);*/

int mt_setfgcolor (enum colors); /*устанавливает цвет последующих выводимых
символов. В качестве параметра передаѐтся константа из созданного Вами перечисли-
мого типа colors , описывающего цвета терминала;*/

int mt_setbgcolor (enum colors); /*устанавливает цвет фона последующих вы-
водимых символов. В качестве параметра передаѐтся константа из созданного Вами
перечислимого типа colors , описывающего цвета терминала.*/

#endif
