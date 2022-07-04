/*
    module  : round.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef ROUND_C
#define ROUND_C

/**
3250  round  :  DA	F  ->  G
G is F rounded to the nearest integer.
*/
double round2(double num)
{
    if (num < 0)
        return -floor(-num + 0.5);
    return floor(num + 0.5);
}

void do_round(void)
{
    double dbl;

    ONEPARAM;
    dbl = GET_AS_DOUBLE(stack[-1]);
    dbl = round2(dbl);
    stack[-1] = MAKE_DOUBLE(dbl);
}
#endif
