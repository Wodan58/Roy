/*
    module  : __latex_manual.c
    version : 1.6
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_LATEX_LOWBAR_MANUAL_C
#define _LOWBAR__LOWBAR_LATEX_LOWBAR_MANUAL_C

#ifdef MANUAL_X
#undef MANUAL_X
#undef MANUAL_C
#endif

#include "manual.c"

/**
2970  __latex_manual  :  N	->
Writes this manual of all Joy primitives to output file in Latex style
but without the head and tail.
*/
void do__lowbar__lowbar_latex_lowbar_manual(void)
{
#ifdef COMPILING
    make_manual(2);
#endif
}
#endif
