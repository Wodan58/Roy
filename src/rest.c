/*
    module  : rest.c
    version : 1.10
    date    : 01/20/20
*/
#ifndef REST_C
#define REST_C

/**
rest  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void do_rest(void)
{
    Stack *list, *quot;

    UNARY;
    list = (Stack *)stack[-1];
    vec_copy(quot, list);
    vec_pop(quot);
    stack[-1] = vec_size(quot) ? (intptr_t)quot : 0;
}
#endif
