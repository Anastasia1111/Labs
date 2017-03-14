#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar (int [2], int x, int y, enum color, enum color);
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos(int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
int bc_bigcharread (int fd, int * big, int need_count, int * count);

#endif
