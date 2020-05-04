/*
    module  : round.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef ROUND_C
#define ROUND_C

double my_round(double num)
{
    if (num < 0)
	return -floor(-num + 0.5);
    return floor(num + 0.5);
}

/**
round  :  F  ->  G
G is F rounded to the nearest integer.
*/
void do_round(void)
{
    real_t dbl;

    UNARY;
    dbl = unpack(stack[-1]);
    dbl = my_round(dbl);
    stack[-1] = pack(dbl);
}
#endif
