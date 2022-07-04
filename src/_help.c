/*
    module  : _help.c
    version : 1.8
    date    : 06/21/22
*/
#ifndef _LOWBAR_HELP_C
#define _LOWBAR_HELP_C

/**
2930  _help  :  N	->
Lists all hidden symbols in library and then all hidden builtin symbols.
*/
void do__lowbar_help(void)
{
#ifdef COMPILING
    long key;
    const char *name;
    int leng, column = 0, start = 1;

    while ((name = dump_help(start, &key)) != 0) {
        if (*name == '_') {
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
