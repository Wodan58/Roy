/*
    module  : put_int.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef PUT_INT_C
#define PUT_INT_C

/**
put_int  :  X  ->
Writes X to output, pops X off stack.
*/
void do_put_int(void)
{
    COMPILE;
    printf("%" PRIdPTR, do_pop());
}
#endif
