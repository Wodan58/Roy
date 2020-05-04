/*
    module  : take_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef TAKE_STR_C
#define TAKE_STR_C

/**
take_str  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void do_take_str(void)
{
    char *str;
    intptr_t num;

    BINARY;
    num = do_pop();
    str = GC_malloc_atomic(num + 2);
    str[0] = '"';
    strncpy(str + 1, (char *)stack[-1], num);
    str[num + 1] = 0;
    stack[-1] = (intptr_t)str | JLAP_INVALID;
}
#endif
