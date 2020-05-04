/*
    module  : strtod.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
strtod  :  S  ->  R
String S is converted to the float R.
*/
void do_strtod(void)
{
    real_t dbl;

    UNARY;
    dbl = strtod((char *)stack[-1], 0);
    stack[-1] = pack(dbl);
}
#endif
