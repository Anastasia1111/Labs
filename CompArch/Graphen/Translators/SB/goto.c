#include "Btranslator.h"

int GoTo(char *param)
{
	int i = 0;
	int stringnum = 0;
	while(param[i] == ' ')
		i++;
	while(param[i] != ' ')
	{
		switch(param[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				stringnum *= 10;
				stringnum += (param[i] - '0');
				++i;
			break;
			default:
				error_log(8);
				return -1;
			break;
		}
	}
	
	struct bcomlist *a = bhead;
	
	while(a != NULL)
	{
		if(a->number == stringnum)
			break;
		}
	while(param[i] == ' ')
		i++;
	if(param[i] == 0 || param[i] == '\n')
	{
		struct acomlist *pcom;
		pcom = (struct acomlist *)malloc(sizeof(struct acomlist));
		pcom->number = COMNUM++;
		if(a != NULL)
			pcom->param = a->anum;
		else
			pcom->param = -2;
		pcom->oper = JUMP;
		pcom->next = NULL;
		if (ahead != NULL)
			atail->next = pcom;
		else
			ahead = pcom;
		atail = pcom;
		return 0;
	}
	else 
	{
		error_log(8);
		return -1;
	}
	return -1;
}
