/*
    module  : app3.c
    version : 1.6
    date    : 06/21/22
*/
#ifndef APP3_C
#define APP3_C

#ifdef UNARY3_X
#undef UNARY3_X
#undef UNARY3_C
#endif

#include "unary3.c"

/**
2560  app3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Obsolescent.  == unary3
*/
void do_app3(void)
{
    do_unary3();
}
#endif
