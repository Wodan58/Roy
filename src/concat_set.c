/*
    module  : concat_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef CONCAT_SET_C
#define CONCAT_SET_C

/**
concat_set  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void do_concat_set(void)
{
    intptr_t set;

    BINARY;
    set = do_pop();
    stack[-1] |= set;
}
#endif
