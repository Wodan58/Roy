/*
    module  : strtol.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef STRTOL_C
#define STRTOL_C

/**
1740  strtol  :  DDA	S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
void do_strtol(void)
{
    int base;

    TWOPARAMS;
    INTEGER;
    base = GET_AS_INTEGER(stack_pop());
    STRING;
    stack[-1] = MAKE_INTEGER(strtol(get_string(stack[-1]), 0, base));
}
#endif
