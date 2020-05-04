/*
    module  : uncons.c
    version : 1.16
    date    : 01/20/20
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
uncons  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void do_uncons(void)
{
    Stack *list, *quot;

    UNARY;
    list = (Stack *)stack[-1];
    stack[-1] = vec_back(list);
    vec_copy(quot, list);
    vec_pop(quot);
    do_push(vec_size(quot) ? (intptr_t)quot : 0);
}
#endif
