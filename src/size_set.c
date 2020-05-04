/*
    module  : size_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef SIZE_SET_C
#define SIZE_SET_C

/**
size_set  :  A  ->  I
Integer I is the number of elements of aggregate A.
*/
void do_size_set(void)
{
    int i, k = 0;
    intptr_t j, set;

    UNARY;
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
	if (set & j)
	    k++;
    stack[-1] = k;
}
#endif
