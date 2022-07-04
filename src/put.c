/*
    module  : put.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef PUT_C
#define PUT_C

/**
3110  put  :  D 	X  ->
Writes X to output, pops X off stack.
*/
void do_put(void)
{
    COMPILE;
    ONEPARAM;
    writefactor(stack_pop());
    putchar(' ');
}
#endif
