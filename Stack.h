#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define	_SP_	0x00000000
#define	_BP_	0x00000001

typedef struct {
	char **l;
	int n;
	int m;
	int sp;
	int bp;
	int size;
} *Stack;

Stack stk_New (int, int);
unsigned int stk_Empty (Stack);
unsigned int stk_Full (Stack);
char *stk_Pop (Stack);
unsigned int stk_Push (Stack, char *);
void stk_Add (Stack, unsigned int, int);
void stk_Mov (Stack, unsigned int, int);

