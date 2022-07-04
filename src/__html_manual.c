/*
    module  : __html_manual.c
    version : 1.6
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_HTML_LOWBAR_MANUAL_C
#define _LOWBAR__LOWBAR_HTML_LOWBAR_MANUAL_C

#ifdef MANUAL_X
#undef MANUAL_X
#undef MANUAL_C
#endif

#include "manual.c"

/**
2960  __html_manual  :  N	->
Writes this manual of all Joy primitives to output file in HTML style.
*/
void do__lowbar__lowbar_html_lowbar_manual(void)
{
#ifdef COMPILING
    make_manual(1);
#endif
}
#endif
