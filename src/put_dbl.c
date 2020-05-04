/*
    module  : put_dbl.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef PUT_DBL_C
#define PUT_DBL_C

/**
put_dbl  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_dbl(void)
{
    COMPILE;
    printf("%g", unpack(do_pop()));
}
#endif
