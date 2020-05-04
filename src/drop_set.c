/*
    module  : drop_set.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef DROP_SET_C
#define DROP_SET_C

/**
drop_set  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void do_drop_set(void)
{
    int i, Value;
    intptr_t set, j;

    BINARY;
    Value = do_pop();
    set = stack[-1];
    for (i = 0, j = 1; i < SETSIZE_ && Value; i++, j <<= 1)
	if (set & j) {
	    set &= ~j;
	    Value--;
	}
    stack[-1] = set;
}
#endif
