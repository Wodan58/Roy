/*
    module  : put_bool.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef PUT_BOOL_C
#define PUT_BOOL_C

/**
put_bool  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_bool(void)
{
    COMPILE;
    printf(do_pop() ? "true" : "false");
}
#endif
