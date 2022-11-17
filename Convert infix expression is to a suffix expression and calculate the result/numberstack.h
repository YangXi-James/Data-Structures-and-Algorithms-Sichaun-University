#pragma once
typedef struct numbernode
{
	float date;
	struct numbernode * pnext;
}*numberpnode, numbernode;

typedef struct numberstack
{
	numberpnode top;
	numberpnode bottom;
}numberstack, * numberpstack;


void pushnumber(numberpstack s, float val);
void travenumberl(numberpstack s);
void initnumber(numberpstack s);
bool emptynumber(numberpstack s);
float popnumber(numberpstack s);
void clearnumber(numberpstack s);
float getvalnumber(numberpstack s);
