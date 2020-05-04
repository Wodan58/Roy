/*
    module  : fold.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef FOLD_C
#define FOLD_C

#ifdef SWAPD_X
#undef SWAPD_X
#undef SWAPD_C
#endif
#ifdef STEP_X
#undef STEP_X
#undef STEP_C
#endif

#include "swapd.c"
#include "step.c"

/**
fold  :  A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
void do_fold(void)
{
    do_swapd();
    do_step();
}
#endif
