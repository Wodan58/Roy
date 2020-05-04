/*
    module  : of_str.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef OF_STR_C
#define OF_STR_C

/**
of_str  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void do_of_str(void)
{
    int index;
    char *str;

    BINARY;
    str = (char *)do_pop();
    index = stack[-1];
    stack[-1] = str[index];
}
#endif
