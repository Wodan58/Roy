/*
    module  : drop_str.c
    version : 1.2
    date    : 03/01/21
*/
#ifndef DROP_STR_C
#define DROP_STR_C

/**
drop_str  :  A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void do_drop_str(void)
{
    intptr_t Value;
    char *str, *result;

    BINARY;
    Value = do_pop();
    str = (char *)stack[-1];
    while (Value-- > 0 && *str)
	str++;
    result = GC_malloc_atomic(strlen(str) + 2);
    sprintf(result, "\"%s", str);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
