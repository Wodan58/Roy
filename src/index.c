/*
    module  : index.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef INDEX_C
#define INDEX_C

#ifdef OF_X
#undef OF_X
#undef OF_C
#endif

#include "of.c"

/**
3200  index  :  DDA	I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
void do_index(void)
{
    do_of();
}
#endif
