/*
    module  : drop_str.c
    version : 1.1
    date    : 01/19/20
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
    strcpy(result, "\"");
    if (str)
	strcpy(result + 1, str);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
