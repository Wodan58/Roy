/*
    module  : at_set.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef AT_SET_C
#define AT_SET_C

/**
at_set  :  A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void do_at_set(void)
{
    int i, index;

    BINARY;
    index = do_pop();
    for (i = 0; i < SETSIZE_; i++) {
	if (stack[-1] & ((intptr_t)1 << i)) {
	    if (!index) {
		stack[-1] = i;
		return;
	    }
	}
	index--;
    }
}
#endif
