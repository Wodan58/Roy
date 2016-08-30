/*
    module  : main.c
    version : 1.1
    date    : 08/30/16
*/
#include <stdio.h>
#include <string.h>
#include "node.h"

int main(int argc, char *argv[])
{
    if (argc > 1)
	if (!strcmp(argv[1], "-c"))
	    compiling = 1;
    return yyparse();
}
