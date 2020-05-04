/*
    module  : size_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef SIZE_STR_C
#define SIZE_STR_C

/**
size_str  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
void do_size_str(void)
{
    UNARY;
    stack[-1] = strlen((char *)stack[-1]);
}
#endif
