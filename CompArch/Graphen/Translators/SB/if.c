#include "Btranslator.h"

int IfOper(char *param)
{
	int i = 0;
	struct varlist *a = vhead;
	int fstnum = -1;
	int flag = 0;
	int minus = 0;
	int stringnum = 0;
	int comp = -2;
	while(param[i] == ' ')
		i++;
	if(param[i] >= 'A' && param[i] <= 'Z')
	{
		while(a != NULL)
		{
			if(a->name[0] == param[i] && a->name[1] == 0)
			{
				fstnum = a->address;
				break;
			}
			a = a->next;
		}
		if(a == NULL)
			flag = 1;
	}
	if(flag)
	{
		error_log(9);
		return -1;
	}
	i++;
	while(param[i] == ' ')
		i++;
	if(strncmp(param + i, ">", 1) == 0)
		comp = 1;
	if(strncmp(param + i, "<", 1) == 0)
		comp = -1;
	if(strncmp(param + i, "==", 2) == 0)
	{
		comp = 0;
		i++;
	}
	if(comp == -2)
	{
		error_log(9);
		return -1;
	}
	i++;
	while(param[i] == ' ')
		i++;
	flag = 0;
	if(param[i] != '0')
	{
		if(param[i] >= 'A' && param[i] <= 'Z') // comparision with var
		{
			a = vhead;
			while(a != NULL)
			{
				if(a->name[0] == param[i] && a->name[1] == 0)
				{
					flag = 1;
					addA(LOAD, fstnum);
					addA(SUB, a->address);
					break;
				}
				a = a->next;
			}
			if(a == NULL)
				flag = 0;
		}
		if(flag == 0)// neither var, nor 0
		{
			error_log(9);
			return -1;
		}
	}
	i++;
	if(flag == 0) // comparision with 0
		addA(LOAD, fstnum);
	switch(comp)
	{
		case 1:
			big_comp(param + i);
			break;
		case 0:
			equal_comp(param + i);
			break;
		case -1:
			small_comp(param + i);
			break;
	}
}

int big_comp(char *param)
{
	struct acomlist *ifstart;
	ifstart = addA(JNEG, -1);
	addA(JZ, -1);
	int end = if_handler(param);// should return NOT -1, error_log inside
	if(end == -1)
		return -1;
	else
	{
		for(int i = 0; i < 2; ++i)
		{
			ifstart->param = COMNUM;// THIS SHOULD POINT TO NEXT AFTER IF COMMAND
			ifstart = ifstart->next;
		}
	}
	return 0;
}

int small_comp(char *param)
{
	struct acomlist *ifstart;
	int par = COMNUM + 2;
	addA(JNEG, par);
	ifstart = addA(JUMP, -1);
	int end = if_handler(param);// should return NOT -1, error_log inside
	if(end == -1)
		return -1;
	else
		ifstart->param = COMNUM;
	return 0;
}

int equal_comp(char *param)
{
	struct acomlist *ifstart;
	int par = COMNUM + 2;
	addA(JNEG, par);
	ifstart = addA(JUMP, -1);
	int end = if_handler(param);// should return NOT -1, error_log inside
	if(end == -1)
		return -1;
	else
		ifstart->param = COMNUM;
	return 0;
}

int if_handler(char *param)
{
	int i = 0;
	enum bcomm oper;
	struct bcomlist *com;
	com = (struct bcomlist *)malloc(sizeof(struct bcomlist));
	if (bhead != NULL)
		btail->next = com;
	else
		bhead = com;
	com->anum = COMNUM;
	com->number = btail->number;
	while(param[i] == ' ')
		i++;
	i += command_translator(param + i, &oper);
	com->oper = oper;
	int ret = 0;
	switch(oper)
	{
		case EMPTY:
			error_log(6);
			return -1;
		case REM:
			return 0;
		case INPUT:
			ret = InOutput(param + i, 1);
			break;
		case OUTPUT:
			ret = InOutput(param + i, 0);
			break;
		case LET:
			ret = RPN(param + i);
			break;
		case GOTO:
			ret = GoTo(param + i);
			break;
		case END:
			end();
			return 1;
	}
	btail = com;
	return ret;
}


