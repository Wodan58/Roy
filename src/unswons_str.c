/*
    module  : unswons_str.c
    version : 1.1
    date    : 01/19/20
*/
#ifndef UNSWONS_STR_C
#define UNSWONS_STR_C

/**
unswons_str  :  A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void do_unswons_str(void)
{
    size_t i;
    char ch, *str, *result;

    UNARY;
    str = (char *)stack[-1];
    ch = *str++;
    if ((i = strlen(str)) == 0)
	stack[-1] = 0;
    else {
	result = GC_malloc_atomic(i + 2);
	result[0] = '"';
	strcpy(result + 1, str);
	stack[-1] = (intptr_t)result | JLAP_INVALID;
    }
    do_push(ch);
}
#endif
