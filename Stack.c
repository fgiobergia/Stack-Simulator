#include "Stack.h"


Stack stk_New (int n, int m) {
	Stack s;
	int i;
	s = malloc (sizeof(*s));
	s->n = n;
	s->m = m;
	s->sp = s->n;
	s->bp = s->sp-1;

	s->l = malloc (s->n*sizeof(char*));
	for (i=0;i<n;i++) {
		s->l[i] = malloc(m+1);
		s->l[i][0] = 0;
	}

	return s;
}

unsigned int stk_Empty (Stack s) {
	return s->sp>=s->n;
}

unsigned int stk_Full (Stack s) {
	return s->sp<=0;
}

char *stk_Pop (Stack s) {
	char *ret;
	if (stk_Empty (s)) {
		return NULL;
	}
	ret = strdup (s->l[s->sp]);
	s->l[s->sp][0] = 0;
	s->sp++;
	return ret;
}

unsigned int stk_Push (Stack s, char *str) {
	int len;
	if (stk_Full(s)) {
		return 0;
	}
	s->sp--;
	len = (strlen(str)>s->m) ? s->m : strlen(str);
	memset (s->l[s->sp], 0, s->m);
	strncpy (s->l[s->sp], str, len);
	return 1;
}

void stk_Add (Stack s, unsigned int reg, int off) {
	switch (reg) {
		case _SP_:
			s->sp += off;
			break;
		case _BP_:
			s->bp += off;
			break;
		default:
			break;
	}
}

void stk_Mov (Stack s, unsigned int reg, int val) {
	switch (reg) {
		case _SP_: 
			s->sp = val;
			break;
		case _BP_:
			s->bp = val;
			break;
		default:
			break;
	}
}
