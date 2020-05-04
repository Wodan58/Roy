/*
    module  : fneg.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FNEG_C
#define FNEG_C

/**
fneg  :  N1  ->  N2
Float N2 is the negative of float N1.
*/
void do_fneg(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    stack[-1] = pack(-dbl);
}
#endif
