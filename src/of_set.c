/*
    module  : of_set.c
    version : 1.2
    date    : 07/23/20
*/
#ifndef OF_SET_C
#define OF_SET_C

/**
of_set  :  I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void do_of_set(void)
{
    int i, index;

    BINARY;
    index = stack[-2];
    for (i = 0; i < SETSIZE_; i++) {
	if (stack[-1] & ((intptr_t)1 << i)) {
	    if (!index) {
		stack[-2] = i;
		do_pop();
		return;
	    }
	}
	index--;
    }
}
#endif
