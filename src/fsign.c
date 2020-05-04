/*
    module  : fsign.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FSIGN_C
#define FSIGN_C

/**
fsign  :  N1  ->  N2
Float N2 is the sign (-1.0 or 0.0 or 1.0) of float N1.
*/
void do_fsign(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    if (dbl)
	dbl = dbl > 0.0 ? 1.0 : -1.0;
    else
	dbl = 0.0;
    stack[-1] = pack(dbl);
}
#endif
