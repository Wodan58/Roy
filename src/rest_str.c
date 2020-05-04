/*
    module  : rest_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef REST_STR_C
#define REST_STR_C

/**
rest_str  :  A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void do_rest_str(void)
{
    size_t i;
    char *str, *result;

    UNARY;
    str = (char *)stack[-1];
    if (!str || (i = strlen(str)) == 0)
	stack[-1] = 0;
    else {
	result = GC_malloc_atomic(i + 2);
	result[0] = '"';
	strcpy(result + 1, str + 1);
	stack[-1] = (intptr_t)result | JLAP_INVALID;
    }
}
#endif
