/*
    module  : fputchars.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FPUTCHARS_C
#define FPUTCHARS_C

/**
fputchars  :  S "abc.."  ->  S
The string abc.. (no quotes) is written to the current position of stream S.
*/
void do_fputchars(void)
{
    char *str;

    COMPILE;
    str = (char *)do_pop();
    fprintf((FILE *)stack[-1], "%s", str);
}
#endif
