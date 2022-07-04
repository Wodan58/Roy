/*
    module  : cons.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef CONS_C
#define CONS_C

/**
2020  cons  :  DDA	X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void cons_lst(void)
{
    Stack *list, *quot;

    list = (Stack *)GET_AS_LIST(stack_pop());
    vec_shallow_copy_take_ownership(quot, list);
    vec_push(quot, stack[-1]);
    stack[-1] = MAKE_LIST(quot);
}

void cons_str(void)
{
    char *str, *result;

    str = get_string(stack_pop());
    result = GC_malloc_atomic(strlen(str) + 3);
    *result = '"';
    CHARACTER;
    result[1] = GET_AS_CHAR(stack[-1]);
    strcpy(result + 2, str);
    stack[-1] = MAKE_USR_STRING(result);
}

void cons_set(void)
{
    CHECKSETMEMBER(stack[-2]);
    stack[-2] = MAKE_SET(
        GET_AS_SET(stack[-1]) | (uint64_t)1 << GET_AS_INTEGER(stack[-2]));
    stack_pop();
}

void do_cons(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-1]))
        cons_lst();
    else if (IS_USR_STRING(stack[-1]))
        cons_str();
    else if (IS_SET(stack[-1]))
        cons_set();
    else
        BADAGGREGATE;
}
#endif
