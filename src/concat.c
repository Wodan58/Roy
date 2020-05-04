/*
    module  : concat.c
    version : 1.15
    date    : 01/20/20
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
concat  :  S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void do_concat(void)
{
    int i, j;
    Stack *first, *second, *result = 0;

    BINARY;
    second = (Stack *)do_pop();
    first = (Stack *)stack[-1];
    if (first || second) {
	if (second)
	    vec_copy(result, second);
	for (i = 0, j = vec_size(first); i < j; i++)
	    vec_push(result, vec_at(first, i));
    }
    stack[-1] = (intptr_t)result;
}
#endif
