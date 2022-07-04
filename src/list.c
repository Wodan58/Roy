/*
    module  : list.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef LIST_C
#define LIST_C

/**
2380  list  :  DA	X  ->  B
Tests whether X is a list.
*/
void do_list(void)
{
    ONEPARAM;
    stack[-1] = MAKE_BOOLEAN(IS_LIST(stack[-1]));
}
#endif
