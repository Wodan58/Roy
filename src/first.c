/*
    module  : first.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef FIRST_C
#define FIRST_C

/**
2040  first  :  DA	A  ->  F
F is the first member of the non-empty aggregate A.
*/
void first_lst(void)
{
    Stack *list;

    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    stack[-1] = vec_back(list);
}

void first_str(void)
{
    char *str;

    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack[-1]);
    stack[-1] = MAKE_CHAR(*str);
}

void first_set(void)
{
    int i;
    uint64_t set, j;

    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            break;
    stack[-1] = MAKE_INTEGER(i);
}

void do_first(void)
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        first_lst();
    else if (IS_USR_STRING(stack[-1]))
        first_str();
    else if (IS_SET(stack[-1]))
        first_set();
    else
        BADAGGREGATE;
}
#endif
