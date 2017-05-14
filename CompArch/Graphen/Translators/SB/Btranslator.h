#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc.c"

#define STR_SIZE 256
FILE *in;
FILE *out;

enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, EMPTY};

struct bcomlist
{
	int number;
	enum bcomm oper;
	char *param;
	struct bcomlist *next;
}*bhead, *btail;

struct acomlist
{
	int number;
	enum commands oper;
	int param;
	struct acomlist *next;
}*ahead, *atail;

struct varlist
{
	struct varlist* next;
	char name[5];
	int address;
}*vhead;

struct oplist
{
	char op;
	struct oplist *next;
};

int COMNUM;
int BRAM[ramSize];
extern int STRN;
enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, EMPTY};

void error_log(int code);
int Btranslate(char *input, int *output);
int command_translator(char *input, enum bcomm *output);
int main(int argc, char* argv[]);
int RPN (enum bcomm *input, int n);

