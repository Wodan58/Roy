/*
    module  : main.c
    version : 1.2
    date    : 07/22/18
*/
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main(int argc, char *argv[])
{
    char *ptr;

    setbuf(stdout, 0);
    if (argc > 1) {
	ptr = argv[1];
	if (*ptr == '-') {
	    while (*++ptr) {
		if (*ptr == 'c')
		    compiling = 1;
		if (*ptr == 'd')
		    debugging = 1;
	    }
	} else if (!freopen(ptr, "r", stdin)) {
	    fprintf(stderr, "failed to open the file '%s'.\n", ptr);
	    exit(1);
	}
    }
    return yyparse();
}
