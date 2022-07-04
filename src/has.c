/*
    module  : has.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef HAS_C
#define HAS_C

/**
2300  has  :  DDA	A X  ->  B
Tests whether aggregate A has X as a member.
*/
void has_lst(void)
{
    int i;
    Stack *list;
    value_t temp;

    temp = stack_pop();
    list = (Stack *)GET_AS_LIST(stack[-1]);
    for (i = vec_size(list) - 1; i >= 0; i--)
        if (!Compare(vec_at(list, i), temp))
            break;
    stack[-1] = MAKE_BOOLEAN(i >= 0);
}

void has_str(void)
{
    char ch, *str;

    ch = GET_AS_CHAR(stack_pop());
    str = get_string(stack[-1]);
    for (; *str && *str != ch; str++)
        ;
    stack[-1] = MAKE_BOOLEAN(*str == ch);
}

void has_set(void)
{
    stack[-2] = MAKE_BOOLEAN(
       (GET_AS_SET(stack[-2]) & (uint64_t)1 << GET_AS_INTEGER(stack[-1])) != 0);
    stack_pop();
}

void do_has(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-2]))
        has_lst();
    else if (IS_USR_STRING(stack[-2]))
        has_str();
    else if (IS_SET(stack[-2]))
        has_set();
    else
        BADAGGREGATE;
}
#endif
