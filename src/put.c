/*
    module  : put.c
    version : 1.11
    date    : 06/23/20
*/
#ifndef PUT_C
#define PUT_C

/**
put  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put(void)
{
    COMPILE;
    if (!stack_empty())
	writefactor(do_pop());
}
#endif
