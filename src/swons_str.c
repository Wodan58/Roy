/*
    module  : swons_str.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef SWONS_STR_C
#define SWONS_STR_C

/**
swons_str  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_swons_str(void)
{
    int ch;
    size_t i;
    char *str, *result;

    BINARY;
    ch = do_pop();
    str = (char *)stack[-1];
    i = str ? strlen(str) : 0;
    result = GC_malloc_atomic(i + 3);
    result[0] = '"';
    result[1] = ch;
    result[2] = 0;
    if (str)
	strcpy(result + 2, str);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
