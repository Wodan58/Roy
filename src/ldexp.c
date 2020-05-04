/*
    module  : ldexp.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef LDEXP_C
#define LDEXP_C

/**
ldexp  :  F I  ->  G
G is F times 2 to the Ith power.
*/
void do_ldexp(void)
{
    int exp;
    real_t dbl;

    BINARY;
    exp = do_pop();
    if (!is_integer(exp))
	execerror("integer", "ldexp");
    dbl = unpack(stack[-1]);
    dbl = ldexp(dbl, exp);
    stack[-1] = pack(dbl);
}
#endif
