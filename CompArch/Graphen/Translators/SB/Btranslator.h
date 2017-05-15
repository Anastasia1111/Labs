#ifndef BTRANSLATOR_H_
#define BTRANSLATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc.h"

#define STR_SIZE 256
FILE *in;
FILE *out;

enum bcomm {REM = 0x1, INPUT, OUTPUT, GOTO, IF, LET, END, EMPTY};

struct bcomlist
{
	int number;
	enum bcomm oper;
	int anum;
	struct bcomlist *next;
};

struct acomlist
{
	int number;
	enum commands oper;
	int param;
	struct acomlist *next;
};

extern struct bcomlist *bhead, *btail;
extern struct acomlist *ahead, *atail;

struct varlist
{
	struct varlist* next;
	char name[5];
	int address;
};

struct oplist
{
	char op;
	struct oplist *next;
};

extern struct varlist *vhead;

struct gotolist
{
	int stringnumber;
	struct gotolist *next;
};

extern struct gotolist *ghead, *gtail;

extern int COMNUM;
int BRAM[ramSize];
extern int STRN;

void error_log(int code);
int Btranslate(char *input);
int command_translator(char *input, enum bcomm *output);
int process_op(char op, char* rpn, int* lci);
int priority(char op);
int RPN(char *input);
int main(int argc, char* argv[]);
int InOutput(char *param, int flag);
int GoTo(char *param);
int IfOper();
int big_comp(char *param);
int small_comp(char *param);
int equal_comp(char *param);
int if_handler(char *param);
int end();
struct acomlist *addA(enum commands oper, int param);

#endif //BTRANSLATOR_H_
