/*
    module  : strtol.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef STRTOL_C
#define STRTOL_C

/**
strtol  :  S I  ->  J
String S is converted to the integer J using base I.
If I = 0, assumes base 10,
but leading "0" means base 8 and leading "0x" means base 16.
*/
void do_strtol(void)
{
    int base;

    BINARY;
    base = do_pop();
    stack[-1] = strtoll((char *)stack[-1], 0, base);
}
#endif
