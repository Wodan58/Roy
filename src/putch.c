/*
    module  : putch.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
putch  :  N  ->
N : numeric, writes character whose ASCII is N.
*/
void do_putch(void)
{
    COMPILE1;
    putchar(do_pop());
}
#endif
