/*
    module  : in.c
    version : 1.13
    date    : 06/21/22
*/
#ifndef IN_C
#define IN_C

/**
2310  in  :  DDA	X A  ->  B
Tests whether X is a member of aggregate A.
*/
void in_lst(void)
{
    int i;
    Stack *list;

    list = (Stack *)GET_AS_LIST(stack_pop());
    for (i = vec_size(list) - 1; i >= 0; i--)
        if (!Compare(stack[-1], vec_at(list, i)))
            break;
    stack[-1] = MAKE_BOOLEAN(i >= 0);
}

void in_str(void)
{
    char ch, *str;

    str = get_string(stack_pop());
    ch = GET_AS_CHAR(stack[-1]);
    for (; *str && *str != ch; str++)
        ;
    stack[-1] = MAKE_BOOLEAN(*str != 0);
}

void in_set(void)
{
    stack[-2] = MAKE_BOOLEAN(
       (GET_AS_SET(stack[-1]) & (uint64_t)1 << GET_AS_INTEGER(stack[-2])) != 0);
    stack_pop();
}

void do_in(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-1]))
        in_lst();
    else if (IS_USR_STRING(stack[-1]))
        in_str();
    else if (IS_SET(stack[-1]))
        in_set();
    else
        BADAGGREGATE;
}
#endif
