#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc.c"

#define STR_SIZE 256
FILE *in;
FILE *out;

enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, EMPTY};

struct comlist
{
	int number;
	bcomm operand;
	char *param;
	comlist *next;
}*head, *next;

struct varlist
{
	char name;
	varlist *next;
}*head, *next;

struct stack
{
	char op;
	stack *next;
};

int BRAM[ramSize];
extern int STRN;
enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, EMPTY};

void error_log(int code);
int Btranslate(char *input, int *output);
int command_translator(char *input, enum bcomm *output);
int main(int argc, char* argv[]);
int RPN (enum bcomm *input, int n);

