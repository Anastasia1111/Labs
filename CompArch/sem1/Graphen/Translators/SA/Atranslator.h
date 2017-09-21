#include <stdio.h>
#include <string.h>
#include "sc.h"

#define STR_SIZE 256
FILE *in;
FILE *out;

extern int STRN;
int BRAM[ramSize];

void error_log(int code);
int translate(char *input, int *output);
int translate_command(char *input, enum commands *output);
int main(int argc, char* argv[]);
