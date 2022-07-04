/*
    module  : fputstring.c
    version : 1.3
    date    : 06/21/22
*/
#ifndef FPUTSTRING_C
#define FPUTSTRING_C

#ifdef FPUTCHARS_X
#undef FPUTCHARS_X
#undef FPUTCHARS_C
#endif

#include "fputchars.c"

/**
1980  fputstring  :  D	S "abc.."  ->  S
== fputchars, as a temporary alternative.
*/
void do_fputstring(void)
{
    do_fputchars();
}
#endif
