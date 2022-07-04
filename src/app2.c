/*
    module  : app2.c
    version : 1.6
    date    : 06/21/22
*/
#ifndef APP2_C
#define APP2_C

#ifdef UNARY2_X
#undef UNARY2_X
#undef UNARY2_C
#endif

#include "unary2.c"

/**
2550  app2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Obsolescent.  ==  unary2
*/
void do_app2(void)
{
    do_unary2();
}
#endif
