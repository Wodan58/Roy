/*
    module  : fold.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef FOLD_C
#define FOLD_C

/**
2800  fold  :  DDDA	A V0 [P]  ->  V
Starting with value V0, sequentially pushes members of aggregate A
and combines with binary operator P to produce value V.
*/
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

void do_fold(void)
{
    THREEPARAMS;
    do_swapd();
    do_step();
}
#endif
