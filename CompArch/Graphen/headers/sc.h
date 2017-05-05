#ifndef SC_LIBS
#define SC_LIBS

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#endif //SC_LIBS

#ifndef SC_H
#define SC_H

#include <stdlib.h>

#define REG_OVERFLOW 0x1
#define REG_ZERO_DIV 0x2
#define REG_OVERLIMIT_MEM 0x3
#define REG_STEP_IGNORE 0x4
#define REG_WR_COM 0x5

#define ramSize 100
int RAM[ramSize];
extern char REG;
extern char InstCount;
extern short int Accum;

enum commands {READ = 10, WRITE = 11, LOAD = 20, STORE = 21, ADD = 30, SUB = 31, DIVIDE = 32, MUL = 33, JUMP = 40,
JNEG = 41, JZ = 42, HALT = 43,  RCR = 63, RCCL = 69};

int sc_memoryInit();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int * value);
int sc_memorySave (char * filename);
int sc_memoryLoad (char * filename);
int sc_regInit (void);
int sc_regSet (int register, int value);
int sc_regGet (int register, int * value);
int sc_commandEncode (int command, int operand, int * value);
int sc_commandDecode (int value, int * command, int * operand);

#endif // SC_H
