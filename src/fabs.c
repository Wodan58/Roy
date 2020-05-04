/*
    module  : fabs.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef FABS_C
#define FABS_C

/**
fabs  :  N1  ->  N2
Float N2 is the absolute value (0.0 ..) of float N1.
*/
void do_fabs(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = fabs(dbl);
    stack[-1] = pack(dbl);
}
#endif
