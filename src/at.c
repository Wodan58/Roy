/*
    module  : at.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef AT_C
#define AT_C

/**
at  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void do_at(void)
{
    int index;
    Stack *Quot;

    BINARY;
    index = do_pop();
    Quot = (Stack *)stack[-1];
    index = vec_size(Quot) - 1 - index;
    stack[-1] = vec_at(Quot, index);
}
#endif
