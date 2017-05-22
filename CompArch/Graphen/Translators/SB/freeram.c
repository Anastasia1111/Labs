#include "Btranslator.h"

int freeram()
{
	int i;
	struct acomlist *a = ahead, *buf1;
	struct bcomlist *b = bhead, *buf2;
	struct gotolist *g = ghead, *buf3;
	struct varlist *v = vhead, *buf4;
	while(a != NULL)
	{
		buf1 = a;
		a = a->next;
		free(buf1);
	}
	while(b != NULL)
	{
		buf2 = b;
		b = b->next;
		free(buf2);
	}
	while(g != NULL)
	{
		buf3 = g;
		g = g->next;
		free(buf3);
	}
	while(v != NULL)
	{
		buf4 = v;
		v = v->next;
		free(buf4);
	}
	return 0;
}
