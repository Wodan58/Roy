/*
    module  : index.c
    version : 1.8
    date    : 01/19/20
*/
#ifndef INDEX_C
#define INDEX_C

/**
index  :  I A  ->  X
X (= A[I]) is the member of A at position I (I = 0,1).
*/
void do_index(void)
{
    int index;
    Stack *Quot;

    BINARY;
    Quot = (Stack *)do_pop();
    index = vec_size(Quot) - 1 - stack[-1];
    stack[-1] = vec_at(Quot, index);
}
#endif
