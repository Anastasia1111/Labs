#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc.c"

#define STR_SIZE 256
FILE *in;
FILE *out;

int BRAM[ramSize];
extern int STRN;

void error_log(int code);
int Btranslate(char *input, int *output);
int main(int argc, char* argv[]);
