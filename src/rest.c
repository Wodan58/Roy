/*
    module  : rest.c
    version : 1.11
    date    : 06/21/22
*/
#ifndef REST_C
#define REST_C

/**
2050  rest  :  DA	A  ->  R
R is the non-empty aggregate A with its first member removed.
*/
void rest_lst(void)
{
    Stack *list, *quot;

    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    vec_shallow_copy(quot, list);
    vec_pop(quot);
    stack[-1] = MAKE_LIST(quot);
}

void rest_str(void)
{
    char *str;

    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack[-1]);
    stack[-1] = MAKE_USR_STRING(stringify(str + 1));
}

void rest_set(void)
{
    int i;
    uint64_t j, set;

    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            break;
    stack[-1] = MAKE_SET(set & ~j);
}

void do_rest(void)
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        rest_lst();
    else if (IS_USR_STRING(stack[-1]))
        rest_str();
    else if (IS_SET(stack[-1]))
        rest_set();
    else
        BADAGGREGATE;
}
#endif
