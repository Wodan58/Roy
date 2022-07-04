/*
    module  : app11.c
    version : 1.10
    date    : 06/21/22
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
2470  app11  :  DDDA	X Y [P]  ->  R
Executes P, pushes result R on stack.
*/
void do_app11(void)
{
    THREEPARAMS;
    ONEQUOTE;
    do_app1();
    do_popd();
}
#endif
