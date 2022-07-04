/*
    module  : putch.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef PUTCH_C
#define PUTCH_C

/**
3120  putch  :  D	N  ->
N : numeric, writes character whose ASCII is N.
*/
void do_putch(void)
{
    value_t temp;

    COMPILE;
    ONEPARAM;
    NUMERICTYPE;
    temp = stack_pop();
    if (IS_INTEGER(temp))
	putchar(GET_AS_INTEGER(temp));
    else if (IS_CHAR(temp))
	putchar(GET_AS_CHAR(temp));
    else if (IS_BOOLEAN(temp))
	putchar(GET_AS_BOOLEAN(temp));
}
#endif
