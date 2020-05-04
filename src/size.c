/*
    module  : size.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef SIZE_C
#define SIZE_C

/**
size  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
void do_size(void)
{
    UNARY;
    stack[-1] = vec_size((Stack *)stack[-1]);
}
#endif
