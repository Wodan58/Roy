/*
    module  : fcompare.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef FCOMPARE_C
#define FCOMPARE_C

/**
fcompare  :  A B  ->  I
I (=-1,0,+1) is the comparison of aggregates A and B.
The values correspond to the predicates <, =, >.
*/
void do_fcompare(void)
{
    real_t dbl1, dbl2;

    BINARY;
    dbl2 = unpack(do_pop());
    dbl1 = unpack(stack[-1]);
    if (dbl1 < dbl2)
	stack[-1] = pack(-1.0);
    else if (dbl2 > dbl1)
	stack[-1] = pack(1.0);
    else
	stack[-1] = pack(0.0);
}
#endif
