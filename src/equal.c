/*
    module  : equal.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef EQUAL_C
#define EQUAL_C

/**
2290  equal  :  DDA	T U  ->  B
(Recursively) tests whether trees T and U are identical.
*/
static int is_equal(value_t first, value_t second);

int is_equal_list(Stack *first, Stack *second)
{
    int i, j;
    value_t First, Second;

    if ((j = vec_size(first)) != vec_size(second))
        return 1; /* unequal */
    for (i = 0; i < j; i++) {
        First = vec_at(first, i);
        Second = vec_at(second, i);
        if (is_equal(First, Second))
            return 1; /* unequal */
    }
    return 0; /* equal */
}

static int is_equal(value_t first, value_t second)
{
    if (IS_LIST(first) && IS_LIST(second))
        return is_equal_list(GET_AS_LIST(first), GET_AS_LIST(second));
    return Compare(first, second);
}

void do_equal(void)
{
    value_t temp;

    TWOPARAMS;
    temp = stack_pop();
    stack[-1] = MAKE_BOOLEAN(!is_equal(stack[-1], temp));
}
#endif
