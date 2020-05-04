/*
    module  : of.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef OF_C
#define OF_C

/**
of  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void do_of(void)
{
    int index;
    Stack *Quot;

    BINARY;
    Quot = (Stack *)do_pop();
    index = vec_size(Quot) - 1 - stack[-1];
    stack[-1] = vec_at(Quot, index);
}
#endif
