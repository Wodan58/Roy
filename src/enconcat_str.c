/*
    module  : enconcat_str.c
    version : 1.4
    date    : 01/19/20
*/
#ifndef ENCONCAT_STR_C
#define ENCONCAT_STR_C

#ifdef SWAPD_X
#undef SWAPD_X
#undef SWAPD_C
#endif
#ifdef CONS_STR_X
#undef CONS_STR_X
#undef CONS_STR_C
#endif
#ifdef CONCAT_STR_X
#undef CONCAT_STR_X
#undef CONCAT_STR_C
#endif

#include "swapd.c"
#include "cons_str.c"
#include "concat_str.c"

/**
enconcat_str  :  X S T  ->  U
Sequence U is the concatenation of sequences S and T
with X inserted between S and T (== swapd cons concat).
*/
void do_enconcat_str(void)
{
    do_swapd();
    do_cons_str();
    do_concat_str();
}
#endif
