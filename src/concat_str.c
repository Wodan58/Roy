/*
    module  : concat_str.c
    version : 1.6
    date    : 01/19/20
*/
#ifndef CONCAT_STR_C
#define CONCAT_STR_C

/**
concat_str  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void do_concat_str(void)
{
    size_t i, j;
    char *first, *second, *result;

    BINARY;
    second = (char *)do_pop();
    first = (char *)stack[-1];
    i = first ? strlen(first) : 0;
    j = second ? strlen(second) : 0;
    result = GC_malloc_atomic(i + j + 2);
    strcpy(result, "\"");
    if (first)
	strcpy(result + 1, first);
    if (second)
	strcpy(result + i + 1, second);
    stack[-1] = (intptr_t)result | JLAP_INVALID;
}
#endif
