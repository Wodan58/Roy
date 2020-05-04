/*
    module  : _help.c
    version : 1.7
    date    : 01/19/20
*/
#ifndef _HELP_C
#define _HELP_C

/**
_help  :  ->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
void do__help(void)
{
#ifdef COMPILING
    khiter_t key;
    Stack *List = 0;
    const char *Name;
    int leng, column = 0, start = 1;

    while ((Name = dump2(start, &key)) != 0) {
	if (*Name == '_') {
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
