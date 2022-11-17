#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include"numberstack.h"

void pushnumber(numberpstack s, float  val)
{
	numberpnode New = (numberpnode)malloc(sizeof(numbernode));
	New->date = val;
	New->pnext = s->top;
	s->top = New;
}

void travelnumber(numberpstack s)
{
	numberpnode p = s->top;
	while (p != NULL && p != s->bottom)
	{
		printf("%c", p->date);
		p = p->pnext;
	}
	printf("\n");
}

void initnumber(numberpstack s)
{

	s->bottom = (numberpnode)malloc(sizeof(numbernode));
	s->top = s->bottom;
	s->bottom->pnext = NULL;
}


bool emptynumber(numberpstack s)
{
	if (s->bottom == s->top)
		return true;
	else
		return false;
}

float popnumber(numberpstack s)
{
	if (empty(s)==true)
		return -1;
	else
	{
		float pnew = s->top->date;
		numberpnode r = s->top;
		s->top = r->pnext;
		free(r);
		r = NULL;
		return pnew;
	}

}
float getvalnumber(numberpstack s)
{
	if (empty(s))
		return -1;
	else
	{
		int pnew = s->top->date;
		return pnew;
	}

}

void clearnumber(numberpstack s)
{
	numberpnode p = (numberpnode)malloc(sizeof(numberpnode));
	p = s->top;
	while (p->pnext != NULL)
	{
		s->top = p->pnext;
		free(p);
		p = s->top;
	}
}
