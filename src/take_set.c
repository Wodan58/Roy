/*
    module  : take_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef TAKE_SET_C
#define TAKE_SET_C

/**
take_set  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void do_take_set(void)
{
    int i, Value;
    intptr_t j, set, result = 0;

    BINARY;
    Value = do_pop();
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_ && Value; i++, j <<= 1)
	if (set & j) {
	    result |= j;
	    Value--;
	}
    stack[-1] = result;
}
#endif
