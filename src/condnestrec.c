/*
    module  : condnestrec.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

#ifdef CONDLINREC_X
#undef CONDLINREC_X
#undef CONDLINREC_C
#endif

#include "condlinrec.c"

/**
2770  condnestrec  :  DU	[ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
void do_condnestrec(void)
{
    do_condlinrec();
}
#endif
