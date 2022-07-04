/*
    module  : uncons.c
    version : 1.17
    date    : 06/21/22
*/
#ifndef UNCONS_C
#define UNCONS_C

/**
2120  uncons  :  DAA	A  ->  F R
F and R are the first and the rest of non-empty aggregate A.
*/
void uncons_lst(void)
{
    Stack *list, *quot;

    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    stack[-1] = vec_back(list);
    vec_shallow_copy(quot, list);
    vec_pop(quot);
    do_push(MAKE_LIST(quot));
}

void uncons_str(void)
{
    char *str;

    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack[-1]);
    stack[-1] = MAKE_CHAR(*str++);
    do_push(MAKE_USR_STRING(stringify(str)));
}

void uncons_set(void)
{
    int i;
    uint64_t j, set;

    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            break;
    stack[-1] = MAKE_INTEGER(i);
    do_push(MAKE_SET(set & ~j));
}

void do_uncons(void)
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        uncons_lst();
    else if (IS_USR_STRING(stack[-1]))
        uncons_str();
    else if (IS_SET(stack[-1]))
        uncons_set();
    else
        BADAGGREGATE;
}
#endif
