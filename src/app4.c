/*
    module  : app4.c
    version : 1.6
    date    : 06/21/22
*/
#ifndef APP4_C
#define APP4_C

#ifdef UNARY4_X
#undef UNARY4_X
#undef UNARY4_C
#endif

#include "unary4.c"

/**
2570  app4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Obsolescent.  == unary4
*/
void do_app4(void)
{
    do_unary4();
}
#endif
