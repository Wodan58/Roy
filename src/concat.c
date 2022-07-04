/*
    module  : concat.c
    version : 1.16
    date    : 06/21/22
*/
#ifndef CONCAT_C
#define CONCAT_C

/**
2160  concat  :  DDA		S T  ->  U
Sequence U is the concatenation of sequences S and T.
*/
void concat_lst(void)
{
    int i, j;
    Stack *first, *second, *result = 0;

    second = (Stack *)GET_AS_LIST(stack_pop());
    first = (Stack *)GET_AS_LIST(stack[-1]);
    if (!vec_size(first) && !vec_size(second))
        vec_init(result);
    else {
        if (vec_size(second))
            vec_copy(result, second);
        for (i = 0, j = vec_size(first); i < j; i++)
            vec_push(result, vec_at(first, i));
    }
    stack[-1] = MAKE_LIST(result);
}

void concat_str(void)
{
    int i, j;
    char *first, *second, *result;

    second = get_string(stack_pop());
    first = get_string(stack[-1]);
    i = strlen(first);
    j = strlen(second);
    result = GC_malloc_atomic(i + j + 2);
    *result = '"';
    strcpy(result + 1, first);
    strcpy(result + i + 1, second);
    stack[-1] = MAKE_USR_STRING(result);
}

void concat_set(void)
{
    uint64_t set;

    set = GET_AS_SET(stack_pop());
    stack[-1] = MAKE_SET(GET_AS_SET(stack[-1]) | set);
}

void do_concat(void)
{
    TWOPARAMS;
    SAME2TYPES;
    if (IS_LIST(stack[-1]))
        concat_lst();
    else if (IS_USR_STRING(stack[-1]))
        concat_str();
    else if (IS_SET(stack[-1]))
        concat_set();
    else
        BADAGGREGATE;
}
#endif
