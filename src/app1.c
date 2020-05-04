/*
    module  : app1.c
    version : 1.10
    date    : 01/19/20
*/
#ifndef APP1_C
#define APP1_C

#ifdef I_X
#undef I_X
#undef I_C
#endif

#include "i.c"

/**
app1  :  X [P]  ->  R
Executes P, pushes result R on stack.
*/
void do_app1(void)
{
    do_i();
}
/* app1 */
#endif
