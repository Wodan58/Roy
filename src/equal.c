/*
    module  : equal.c
    version : 1.13
    date    : 01/19/20
*/
#ifndef EQUAL_C
#define EQUAL_C

int equal(Stack *first, Stack *second)
{
    int i;
    intptr_t First, Second;

    if ((i = vec_size(first)) != vec_size(second))
	return 0;
    for (--i; i >= 0; i--) {
	First = vec_at(first, i);
	Second = vec_at(second, i);
	if (is_list(First) && is_list(Second)) {
	    if (!equal((Stack *)First, (Stack *)Second))
		return 0;
	} else if (is_string(First) && is_string(Second)) {
	    if (strcmp((char *)First, (char *)Second))
		return 0;
	} else if (First != Second)
	    return 0;
    }
    return 1;
}

/**
equal  :  T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
void do_equal(void)
{
    BINARY;
    if (is_list(stack[-2]) && is_list(stack[-1]))
	stack[-2] = equal((Stack *)stack[-2], (Stack *)stack[-1]);
    else
	stack[-2] = stack[-2] == stack[-1];
    do_zap();
}
#endif
