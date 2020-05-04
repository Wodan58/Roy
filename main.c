/*
    module  : main.c
    version : 1.15
    date    : 01/19/20
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <setjmp.h>
#include "decl.h"

void inilinebuffer(char *ptr);	/* yylex.c */

void init_heap(void);		/* print.c */

void init_stack(void);		/* stack.c */

void init_decl(void);		/* compile.c */

int yyparse(void);		/* parse.c */

int autoput = INIAUTOPUT, tracegc = INITRACEGC, undeferror = INIUNDEFERR;
int g_argc, compiling, debugging;
char **g_argv, *filename;
clock_t startclock;
static jmp_buf begin;

void execerror(char *message, const char *op)
{
    if (op && !strncmp(op, "do_", 3))
	op += 3;
    if (op && message)
	printf("run time error: %s needed for %s\n", message, op);
    longjmp(begin, 1);
}

int main(int argc, char *argv[])
{
    char *ptr;
    int rv = 0;

    startclock = clock();
    init_heap();
    init_stack();
    init_decl();
    if (argc > 1) {
	ptr = argv[rv = 1];
	if (*ptr == '-') {
	    rv = 2;
	    while (*++ptr) {
		if (*ptr == 'c')
		    compiling = 1;
		if (*ptr == 'd')
		    debugging = 1;
	    }
	}
	ptr = argv[rv];
	if (!ptr || isdigit(*ptr))
	    rv--;
        else if (!freopen(filename = ptr, "r", stdin)) {
	    fprintf(stderr, "failed to open the file '%s'.\n", ptr);
	    return 0;
	}
    }
    g_argc = argc - rv;
    g_argv = &argv[rv];
    setjmp(begin);
    return yyparse();
}
