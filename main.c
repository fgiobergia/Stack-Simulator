#include <ncurses.h>
#include "Stack.h"

#define	abs(x)	(x<0)?-x:x

void usage () {
	printf ("Stack simulator\n"
	        "stack [params]\n"
		"  -n ROWS: number of rows\n"
		"  -m COLS: number of columns\n"
		"  -w SIZE: words size\n");
	exit(0);
}

void signprintw (int y, int x, int n) {
	char ch;
	ch = (n<0) ? '-' : '+';
	if (!n) {
		mvprintw (y, x, "  -  ");
	}
	else {
		mvprintw (y, x, "%c0x%.02x", ch,abs(n));
	}
}

int main (int argc, char *argv[]) {
	int y, x, n, m, i, size, val, reg;
	char fstr[16], *cmd;
	char *dashes, *arg;
	Stack s;
	n = -1;
	m = -1;
	size = -1;
	for (i=1;i<argc-1;i++) {
		if (!strcmp(argv[i],"-n")) {
			n = atoi(argv[i+1]);
		}
		else if (!strcmp(argv[i],"-m")) {
			m = atoi(argv[i+1]);
		}
		else if (!strcmp(argv[i],"-w")) {
			size = atoi(argv[i+1]);
		}
	}
	if (n<0 || m<0 || size<0) {
		usage ();
	}
	initscr ();
	raw ();
	getmaxyx(stdscr, y, x);
	s = stk_New (n, m);
	dashes = malloc (m+3);
	memset (dashes+1, '-', m);
	dashes[m+2] = 0;
	dashes[m+1] = '+';
	dashes[0] = '+';
	arg = NULL;
	cmd = malloc (15+m);
	while (1) {
		clear ();
		mvprintw (0, 4, "sp    bp");

		mvprintw (1, 2,"%04x  %04x",s->sp*size,s->bp*size);
		/* Display stack */
		for (i=0;i<n;i++) {
			signprintw (2*i+3, 1, (i-s->sp)*size);
			signprintw (2*i+3, 7, (i-s->bp)*size);
			mvprintw (2*i+2, 16, dashes);
			mvprintw (2*i+3, 16, "|%*s",(m+strlen(s->l[i]))/2, s->l[i]);
			mvaddch(2*i+3, 17+m, '|');
		}
		mvprintw (2*i+2, 16, dashes);

		/* Display SP */
		mvprintw (2*s->sp+3, m+19, "<= sp");

		/* Display BP */
		mvprintw (2*s->bp+3, m+19, (s->sp!=s->bp)?"<= bp":"<= sp, bp");

		if (arg!=NULL) {
			mvprintw (n*2+6, 2, arg);
		}
		move (n*2+5, 2);
		printw ("> ");
		getnstr (cmd, 14+m);

		if (!strncasecmp("push ",cmd, 5)) {
			arg = malloc (m);
			stk_Push (s, cmd+5);
			arg = NULL;
		}
		else if (!strncasecmp("pop",cmd, 3)) {
			arg = stk_Pop (s);
		}
		else if (!strncasecmp("mov ",cmd,4) || !strncasecmp("add ",cmd,4) || !strncasecmp("sub ",cmd,4)) {
			arg = malloc (4);
			sscanf (cmd+3,"%x, %4s",&val,arg);
			val /= size; 

			if (!strcasecmp(arg, "sp")) {
				reg = _SP_;
			}
			else if (!strcasecmp(arg, "bp")) {
				reg = _BP_;
			}
			else {
				arg = strdup("No such register");
				reg = -1;
			}
			if (reg!=-1) {
				if (!strncasecmp("add ",cmd,4) || !strncasecmp("sub ",cmd,4)) {
					val *= (cmd[0]=='a')?1:-1; // sub x = add -x
					stk_Add (s, reg, val);
				}
				else {
					stk_Mov (s, reg, val);
				}
				arg = NULL;
			}
		}
		else if (!strcasecmp ("quit",cmd)) {
			break;
		}
		else {
			arg = strdup ("No such command");
		}
		refresh ();
	}
	endwin();
	return 0;
}

