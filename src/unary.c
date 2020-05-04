/*
    module  : unary.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef UNARY_C
#define UNARY_C

#ifdef STACK_X
#undef STACK_X
#undef STACK_C
#endif
#ifdef SWAP_X
#undef SWAP_X
#undef SWAP_C
#endif
#ifdef DIP_X
#undef DIP_X
#undef DIP_C
#endif
#ifdef REST_X
#undef REST_X
#undef REST_C
#endif
#ifdef CONS_X
#undef CONS_X
#undef CONS_C
#endif
#ifdef UNSTACK_X
#undef UNSTACK_X
#undef UNSTACK_C
#endif

#include "stack.c"
#include "swap.c"
#include "dip.c"
#include "rest.c"
#include "cons.c"
#include "unstack.c"

/**
unary  :  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void do_unary(void)
{
    do_stack();
    do_swap();
    do_dip();
    do_rest();
    do_rest();
    do_cons();
    lst2stk((Stack *)do_pop());
}
#endif
