/*
    module  : help.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef HELP_C
#define HELP_C

/**
help  :  ->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
void do_help(void)
{
#ifdef COMPILING
    khiter_t key;
    Stack *List = 0;
    const char *Name;
    int leng, column = 0, start = 1;

    while ((Name = dump2(start, &key)) != 0) {
	if (*Name != '_' && !isdigit(*Name)) {
	    leng = strlen(Name) + 1;
	    if (column + leng > LINEWIDTH) {
		putchar('\n');
		column = 0;
	    }
	    printf("%s ", Name);
	    column += leng;
	}
	start = 0;
    }
    putchar('\n');
#endif
}
#endif
