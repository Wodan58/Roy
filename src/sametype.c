/*
    module  : sametype.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef SAMETYPE_C
#define SAMETYPE_C

/**
2320  sametype  :  DDA	X Y  ->  B
Tests whether X and Y have the same type.
*/
void do_sametype(void)
{
    int type1, type2;

    TWOPARAMS;
    type2 = get_type(stack_pop());
    type1 = get_type(stack[-1]);
    stack[-1] = MAKE_BOOLEAN(type1 == type2);
}
#endif
