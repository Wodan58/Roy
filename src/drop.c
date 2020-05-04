/*
    module  : drop.c
    version : 1.11
    date    : 01/20/20
*/
#ifndef DROP_C
#define DROP_C

/**
drop  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void do_drop(void)
{
    Stack *List;
    intptr_t Value;

    BINARY;
    Value = do_pop();
    vec_copy(List, (Stack *)stack[-1]);
    vec_setsize(List, vec_size(List) - Value);
    stack[-1] = (intptr_t)List;
}
#endif
