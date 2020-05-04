/*
    module  : getch.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef GETCH_C
#define GETCH_C

/**
getch  :  ->  N
Reads a character from input and puts it onto stack.
*/
void do_getch(void)
{
    COMPILE;
    do_push(getchar());
}
#endif
