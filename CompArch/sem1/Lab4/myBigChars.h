#ifndef MYBIGCHARS_H
#define MYBIGCHARS_H

#define _0_0_ 0x81C3663C
#define _0_1_ 0x3C66C381
#define _1_0_ 0x181C1810
#define _1_1_ 0x3C181818
#define _2_0_ 0x3062663C
#define _2_1_ 0x7E660C18
#define _3_0_ 0x78C0633E
#define _3_1_ 0x3E63C078
#define _4_0_ 0x24283020
#define _4_1_ 0x2020203F
#define _5_0_ 0x7B03037E
#define _5_1_ 0x7EC380CF
#define _6_0_ 0x7F03C67C
#define _6_1_ 0x7EC3C3C3
#define _7_0_ 0x183063FF
#define _7_1_ 0x03060C7E
#define _8_0_ 0x7EC3C37E
#define _8_1_ 0x7EC3C37E
#define _9_0_ 0x7C66663C
#define _9_1_ 0x1C306060
#define _A_0_ 0x6666663C
#define _A_1_ 0x66667E7E
#define _B_0_ 0x3E66663E
#define _B_1_ 0x3E66663E
#define _C_0_ 0x0666763C
#define _C_1_ 0x3C766606
#define _D_0_ 0x6666663E
#define _D_1_ 0x3E666666
#define _E_0_ 0x7E06067E
#define _E_1_ 0x7E060606
#define _F_0_ 0x06067E7E
#define _F_1_ 0x06063E3E

#define _0 {0x81C3663C, 0x3C66C381}
#define _1 {0x181C1810, 0x3C181818}
#define _2 {0x3062663C, 0x7E660C18}
#define _3 {0x78C0633E, 0x3E63C078}
#define _4 {0x24283020, 0x2020203F}
#define _5 {0x7B03037E, 0x7EC380CF}
#define _6 {0x7F03C67C, 0x7EC3C3C3}
#define _7 {0x183063FF, 0x03060C7E}
#define _8 {0x7EC3C37E, 0x7EC3C37E}
#define _9 {0x7C66663C, 0x1C306060}
#define _A {0x6666663C, 0x66667E7E}
#define _B {0x3E66663E, 0x3E66663E}
#define _C {0x0666763C, 0x3C766606}
#define _D {0x6666663E, 0x3E666666}
#define _E {0x7E06067E, 0x7E060606}
#define _F {0x06067E7E, 0x06063E3E}

#define _P_ {0x7E181800, 0x0018187E}

#include <string.h>
#include "myTerm.h"

int bc_printA (char * str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar (int [2], int x, int y, enum colors, enum colors);
int bc_setbigcharpos (int * big, int x, int y, int value);
int bc_getbigcharpos(int * big, int x, int y, int *value);
int bc_bigcharwrite (int fd, int * big, int count);
int bc_bigcharread (int fd, int * big, int need_count, int * count);

#endif
