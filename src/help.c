/*
    module  : help.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef HELP_C
#define HELP_C

/**
2920  help  :  N	->
Lists all defined symbols, including those from library files.
Then lists all primitives of raw Joy.
(There is a variant: "_help" which lists hidden symbols).
*/
void do_help(void)
{
#ifdef COMPILING
    long key;
    const char *name;
    int leng, column = 0, start = 1;

    while ((name = dump_help(start, &key)) != 0) {
        if (*name != '_' && !isdigit(*name)) {
            leng = strlen(name) + 1;
            if (column + leng > LINEWIDTH) {
                putchar('\n');
                column = 0;
            }
            printf("%s ", name);
            column += leng;
        }
        start = 0;
    }
    putchar('\n');
#endif
}
#endif
