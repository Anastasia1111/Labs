#include "Btranslator.h"

int InOutput(char * param, int flag)
{
	int i = 0;
	while(param[i] == ' ')
		i++;
	if(param[i] < 'A' || param[i] > 'Z')
	{
		error_log(7);
		return -1;
	}
	
	struct varlist *a = vhead;
	while(a != NULL)
	{
		if(a->name[0] == param[i] && a->name[1] == 0)
			break;
		a = a->next;
	}
	if(a == NULL)
	{
		if(flag == 1)
		{
			a = malloc(sizeof(struct varlist));
			a->name[0] = param[i];
			a->name[1] = 0;
			if(vhead == NULL)
				a->address = 99;
			else
				a->address = vhead->address - 1;
			a->next = vhead;
			vhead = a;
		} else {
			error_log(7);
			return -1;
		}
	}
	struct acomlist *pcom;
	pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
	pcom->number = COMNUM++;
	pcom->param = a->address;
	if(flag == 1)
		pcom->oper = READ;
	else
		pcom->oper = WRITE;
	pcom->next = NULL;
	if (ahead!=NULL)
		atail->next = pcom;
	else
		ahead = pcom;
	atail = pcom;
	
	i++;
	while(param[i] == ' ')
		i++;
	if(param[i] != '\n')
	{
		error_log(7);
		return -1;
	}
}
