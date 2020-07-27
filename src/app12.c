/*
    module  : app12.c
    version : 1.10
    date    : 07/23/20
*/
#ifndef APP12_C
#define APP12_C

#ifdef UNARY2_X
#undef UNARY2_X
#undef UNARY2_C
#endif
#ifdef ROLLDOWN_X
#undef ROLLDOWN_X
#undef ROLLDOWN_C
#endif

#include "unary2.c"
#include "rolldown.c"

/**
app12  :  X Y1 Y2 [P]  ->  R1 R2
Executes P twice, with Y1 and Y2, returns R1 and R2.
*/
void do_app12(void)
{
    do_unary2();
    do_rolldown();
    do_pop();
}
#endif
