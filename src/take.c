/*
    module  : take.c
    version : 1.14
    date    : 01/20/20
*/
#ifndef TAKE_C
#define TAKE_C

/**
take  :  A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void do_take(void)
{
    int i, leng;
    intptr_t num;
    Stack *list, *result = 0;

    BINARY;
    num = do_pop();
    list = (Stack *)stack[-1];
    leng = vec_size(list);
    for (i = leng - num; i < leng; i++)
	vec_push(result, vec_at(list, i));
    stack[-1] = (intptr_t)result;
}
#endif
