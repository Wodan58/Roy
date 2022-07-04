/*
    module  : enconcat.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef ENCONCAT_C
#define ENCONCAT_C

/**
2170  enconcat  :  DDDA 	X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
#ifdef SWAPD_X
#undef SWAPD_X
#undef SWAPD_C
#endif
#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif
#ifdef CONCAT_X
#undef CONCAT_X
#undef CONCAT_C
#endif

#include "swapd.c"
#include "cons.c"
#include "concat.c"

void do_enconcat(void)
{
    THREEPARAMS;
    SAME2TYPES;
    do_swapd();
    do_cons();
    do_concat();
}
#endif
