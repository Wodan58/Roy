/*
    module  : list.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef LIST_C
#define LIST_C

/**
list  :  X  ->  B
Tests whether X is a list.
*/
void do_list(void)
{
    UNARY;
    stack[-1] = is_list(stack[-1]);
}
#endif
