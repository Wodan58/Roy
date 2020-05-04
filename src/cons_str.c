/*
    module  : cons_str.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef CONS_STR_C
#define CONS_STR_C

/**
cons_str  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_cons_str(void)
{
    size_t i;
    char *str, *result;

    BINARY;
    str = (char *)do_pop();
    i = str ? strlen(str) : 0;
    result = GC_malloc_atomic(i + 3);
    result[0] = '"';
    result[1] = stack[-1];
    result[2] = 0;
    if (str)
	strcpy(result + 2, str);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
