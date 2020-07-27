/*
    module  : putch.c
    version : 1.12
    date    : 06/23/20
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
void do_putch(void)
{
    COMPILE;
    putchar(do_pop());
}
#endif
