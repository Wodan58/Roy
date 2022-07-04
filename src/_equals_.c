/*
    module  : _equals_.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef _EQUALS__C
#define _EQUALS__C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
2280  =  :  DDA 	X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X is equal to Y.  Also supports float.
*/
void do__equals_(void)
{
    do_equal();
}
#endif
