/*
    module  : getch.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef GETCH_C
#define GETCH_C

/**
3100  getch  :  A	->  N
Reads a character from input and puts it onto stack.
*/
void do_getch(void)
{
    COMPILE;
    do_push(MAKE_CHAR(getchar()));
}
#endif
