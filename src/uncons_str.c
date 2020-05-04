/*
    module  : uncons_str.c
    version : 1.5
    date    : 01/19/20
*/
#ifndef UNCONS_STR_C
#define UNCONS_STR_C

/**
uncons_str  :  A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void do_uncons_str(void)
{
    size_t i;
    char *str, *result;

    UNARY;
    str = (char *)stack[-1];
    stack[-1] = *str++;
    if ((i = strlen(str)) == 0)
	do_push(0);
    else {
	result = GC_malloc_atomic(i + 2);
	result[0] = '"';
	strcpy(result + 1, str);
	do_push((intptr_t)result | JLAP_INVALID);
    }
}
#endif
