#include "Btranslator.h"

struct acomlist *addA(enum commands oper, int param)
{
	struct acomlist *pcom;
	pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
	pcom->number = COMNUM++;
	pcom->param = param;
	pcom->oper = oper;
	pcom->next = NULL;
	if (ahead != NULL)
		atail->next = pcom;
	else
		ahead = pcom;
	atail = pcom;
	return pcom;
}
