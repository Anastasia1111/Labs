#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>


//extern char clear[];

enum colors { BLACK = 30, RED, GREEN, YELLOW, BLUE, PURPLE, TURQUO, WHITE };
//enum gnomecolors {BLACK = 30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN = 36, LGRAY = 37, DEF = 39, DGRAY = 90, LRED = 91, LGREEN = 92,
//	LYELLOW = 93, LBLUE = 94, LMAGENTA = 95, LCEAN = 96, WHITE = 97 };

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
