#include "Btranslator.h"

int end()
{
	struct acomlist *pcom;
	pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
	pcom->number = COMNUM++;
	pcom->param = 0;
	pcom->oper = HALT;
	pcom->next = NULL;
	if (ahead != NULL)
		atail->next = pcom;
	else
		ahead = pcom;
	atail = pcom;
	return 0;
}
