/*
    module  : main.c
    version : 1.9
    date    : 07/08/19
*/
#include <stdio.h>
#include <ctype.h>

void init_heap(void);		/* print.c */

void init_stack(void);		/* builtin.c */

int yyparse(void);		/* parse.c */

int compiling, debugging;
int g_argc;
char **g_argv;

int main(int argc, char *argv[])
{
    char *ptr;
    int rv = 0;

    init_heap();
    init_stack();
    if (argc > 1) {
	rv = 1;
	ptr = argv[1];
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
        else if (!freopen(ptr, "r", stdin)) {
	    fprintf(stderr, "failed to open the file '%s'.\n", ptr);
	    return 0;
	}
    }
    g_argc = argc - rv;
    g_argv = &argv[rv];
    return yyparse();
}
