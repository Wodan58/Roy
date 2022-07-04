/*
    module  : app1.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef APP1_C
#define APP1_C

#ifdef I_X
#undef I_X
#undef I_C
#endif

#include "i.c"

/**
2460  app1  :  DDA	X [P]  ->  R
Executes P, pushes result R on stack.
*/
void do_app1(void)
{
    TWOPARAMS;
    ONEQUOTE;
    do_i();
}
#endif
