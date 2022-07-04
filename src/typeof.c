/*
    module  : typeof.c
    version : 1.2
    date    : 06/21/22
*/
#ifndef TYPEOF_C
#define TYPEOF_C

/**
3260  typeof  :  DA	X  ->  I
Replace X by its type.
*/
void do_typeof(void)
{
    ONEPARAM;
    stack[-1] = MAKE_INTEGER(get_type(stack[-1]));
}
#endif
