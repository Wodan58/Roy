/*
    module  : strtod.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef STRTOD_C
#define STRTOD_C

/**
1750  strtod  :  DA	S  ->  R
String S is converted to the float R.
*/
void do_strtod(void)
{
    double dbl;

    ONEPARAM;
    STRING;
    dbl = strtod(get_string(stack[-1]), 0);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
