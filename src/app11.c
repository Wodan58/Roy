/*
    module  : app11.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef APP11_C
#define APP11_C

#ifdef APP1_X
#undef APP1_X
#undef APP1_C
#endif
#ifdef POPD_X
#undef POPD_X
#undef POPD_C
#endif

#include "app1.c"
#include "popd.c"

/**
app11  :  X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void do_app11(void)
{
    do_app1();
    do_popd();
}
#endif
