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
}*bhead = NULL, *btail = NULL;

struct acomlist
{
	int number;
	enum commands oper;
	int param;
	struct acomlist *next;
}*ahead = NULL, *atail = NULL;

struct varlist
{
	struct varlist* next;
	char name[5];
	int address;
}*vhead = NULL;

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
int process_op(char op, char* rpn, int* lci);
int priority(char op);
int RPN(char *input);
int main(int argc, char* argv[]);
int InOutput(char *param);
int GoTo(char *param);
int end();


