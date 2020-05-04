/*
    module  : enconcat_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef ENCONCAT_SET_C
#define ENCONCAT_SET_C

#ifdef SWAPD_X
#undef SWAPD_X
#undef SWAPD_C
#endif
#ifdef CONS_SET_X
#undef CONS_SET_X
#undef CONS_SET_C
#endif
#ifdef CONCAT_SET_X
#undef CONCAT_SET_X
#undef CONCAT_SET_C
#endif

#include "swapd.c"
#include "cons_set.c"
#include "concat_set.c"

/**
enconcat_set  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
void do_enconcat_set(void)
{
    do_swapd();
    do_cons_set();
    do_concat_set();
}
#endif
