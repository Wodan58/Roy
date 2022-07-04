/*
    module  : swons.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef SWONS_C
#define SWONS_C

/**
2030  swons  :  DDA	A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void swons_lst(void)
{
    value_t temp;
    Stack *list, *quot;

    temp = stack_pop();
    list = (Stack *)GET_AS_LIST(stack[-1]);
    vec_shallow_copy_take_ownership(quot, list);
    vec_push(quot, temp);
    stack[-1] = MAKE_LIST(quot);
}

void swons_str(void)
{
    char ch, *str, *result;

    CHARACTER;
    ch = GET_AS_CHAR(stack_pop());
    str = get_string(stack[-1]);
    result = GC_malloc_atomic(strlen(str) + 3);
    *result = '"';
    result[1] = ch;
    strcpy(result + 2, str);
    stack[-1] = MAKE_USR_STRING(result);
}

void swons_set(void)
{
    CHECKSETMEMBER(stack[-1]);
    stack[-2] = MAKE_SET(
        GET_AS_SET(stack[-2]) | (uint64_t)1 << GET_AS_INTEGER(stack[-1]));
    stack_pop();
}

void do_swons(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-2]))
        swons_lst();
    else if (IS_USR_STRING(stack[-2]))
        swons_str();
    else if (IS_SET(stack[-2]))
        swons_set();
    else
        BADAGGREGATE;
}
#endif
