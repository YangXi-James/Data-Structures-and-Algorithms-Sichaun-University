#pragma once
#include<stdbool.h>
typedef struct node
{
	 char date;
	struct node * pnext;
}*pnode, node;

typedef struct stack
{
	pnode top;
	pnode bottom;
}stack, *pstack;


void push(pstack s, char val);
void travel(pstack s);
void init(pstack s);
bool empty(pstack s);
char pop(pstack s);
void clear(pstack s);
char getval(pstack s);
