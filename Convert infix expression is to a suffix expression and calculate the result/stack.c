#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include"stack.h"

void push(pstack s, char  val)
{
	pnode New = (pnode)malloc(sizeof(node));
	New->date = val;
	New->pnext = s->top;
	s->top = New;
}

void travel(pstack s)
{
	pnode p = s->top;
	while (p != NULL && p != s->bottom)
	{
		printf("%c", p->date);
		p = p->pnext;
	}
	printf("\n");
}

void init(pstack s)
{

	s->bottom = (pnode)malloc(sizeof(node));
	s->top = s->bottom;
	s->bottom->pnext = NULL;
}


bool empty(pstack s)
{
	if (s->bottom == s->top)
		return true;
	else
		return false;
}

char pop(pstack s)
{
	if (empty(s)==true)
		return ' ';
	else
	{
		char pnew = s->top->date;
		pnode r = s->top;
		s->top = r->pnext;
		free(r);
		r = NULL;
		return pnew;
	}

}
char getval(pstack s)
{
	if (empty(s))
		return ' ';
	else
	{
		char pnew = s->top->date;
		return pnew;
	}

}

void clear(pstack s)
{
	pnode p = (pnode)malloc(sizeof(node));
	p = s->top;
	while (p->pnext != NULL)
	{
		s->top = p->pnext;
		free(p);
		p = s->top;
	}
}
