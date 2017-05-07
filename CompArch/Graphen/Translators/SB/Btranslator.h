#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc.c"

#define STR_SIZE 256
FILE *in;
FILE *out;

int BRAM[ramSize];
extern int STRN;
enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, BIG, LES, EQUALITY, EQUAL, PLUS, MINUS, MULTI, DIVIS, LBRACK, RBRACK, VAR, EMPTY};

void error_log(int code);
int Btranslate(char *input, int *output);
int command_translator(char *input, enum bcomm *output);
int main(int argc, char* argv[]);
