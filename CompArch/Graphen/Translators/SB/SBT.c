#include "Btranslator.h"

int STRN = 1;
int COMNUM = 0;
struct acomlist *ahead = NULL, *atail = NULL;
struct bcomlist *bhead = NULL, *btail = NULL;
struct gotolist *ghead = NULL, *gtail = NULL;
struct varlist *vhead = NULL;


int main(int argc, char* argv[])
{
	int i;
	char string[STR_SIZE];
	
	for(i = 0; i < ramSize; ++i)
		BRAM[i] = 0;
	if(argc < 3)
	{
		error_log(1);
		return 1;
	}
	
	in = fopen(argv[1], "r");
	if(in == NULL)
	{
		error_log(2);
		return 1;
	}
	
	
	
	out = fopen(argv[2], "w");
	fwrite(BRAM, sizeof(int), ramSize, out);
	int flag;
	do {
		if(fgets(string, sizeof(string), in) == NULL)
		{
			if(feof(in) != 0)
			{
				break;
			} else {
				error_log(3);
				return 1;
			}
		}
		
		flag = Btranslate(string);
		if(flag == -1)
			return 1;
		STRN++;
		if(flag == 100)
			continue;
		if(flag == 1)
			break;
	} while (1);
	
	
	struct acomlist *a = ahead;
	struct gotolist *g = ghead;
	struct bcomlist *b = bhead;
	while(a != NULL)
	{
		if(a->param == -100)
		{
			while(b != NULL)
			{
				if(b->number == g->stringnumber)
				{
					a->param = b->anum;
					break;
				}
				b = b->next;
			}
			b = bhead;
			g = g->next;
		}
		a = a->next;
	}
	
	a = ahead;
	while(a != NULL)
	{
		fprintf(stderr, "%d ", a->number);
		switch(a->oper)
		{
			case READ:
				fprintf(stderr, "READ ");
				break;
			case WRITE:
				fprintf(stderr, "WRITE ");
				break;
			case LOAD:
				fprintf(stderr, "LOAD ");
				break;
			case STORE:
				fprintf(stderr, "STORE ");
				break;
			case ADD:
				fprintf(stderr, "ADD ");
				break;
			case SUB:
				fprintf(stderr, "SUB ");
				break;
			case DIVIDE:
				fprintf(stderr, "DIVIDE ");
				break;
			case MUL:
				fprintf(stderr, "MUL ");
				break;
			case JUMP:
				fprintf(stderr, "JUMP ");
				break;
			case JNEG:
				fprintf(stderr, "JNEG ");
				break;
			case JZ:
				fprintf(stderr, "JZ ");
				break;
			case HALT:
				fprintf(stderr, "HALT ");
				break;
			case EQU:
				fprintf(stderr, "= ");
				break;
		}
		if(a->oper == EQU)
			fprintf(stderr, "%04X\n", a->param);
		else
			fprintf(stderr, "%d\n", a->param);
		a = a->next;
	}
	a = ahead;
	while(a != NULL)
	{
		fprintf(out, "%d ", a->number);
		switch(a->oper)
		{
			case READ:
				fprintf(out, "READ ");
				break;
			case WRITE:
				fprintf(out, "WRITE ");
				break;
			case LOAD:
				fprintf(out, "LOAD ");
				break;
			case STORE:
				fprintf(out, "STORE ");
				break;
			case ADD:
				fprintf(out, "ADD ");
				break;
			case SUB:
				fprintf(out, "SUB ");
				break;
			case DIVIDE:
				fprintf(out, "DIVIDE ");
				break;
			case MUL:
				fprintf(out, "MUL ");
				break;
			case JUMP:
				fprintf(out, "JUMP ");
				break;
			case JNEG:
				fprintf(out, "JNEG ");
				break;
			case JZ:
				fprintf(out, "JZ ");
				break;
			case HALT:
				fprintf(out, "HALT ");
				break;
			case EQU:
				fprintf(out, "= ");
				break;
		}
		if(a->oper == EQU)
			fprintf(out, "%04X\n", a->param);
		else
			fprintf(out, "%d\n", a->param);
		a = a->next;
	}
	
	fclose(in),
	fclose(out);
	return 0;
}
