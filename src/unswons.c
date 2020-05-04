/*
    module  : unswons.c
    version : 1.11
    date    : 01/20/20
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
unswons  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void do_unswons(void)
{
    Stack *list, *quot;

    UNARY;
    list = (Stack *)stack[-1];
    do_push(vec_back(list));
    vec_copy(quot, list);
    vec_pop(quot);
    stack[-2] = vec_size(quot) ? (intptr_t)quot : 0;
}
#endif
