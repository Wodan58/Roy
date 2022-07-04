/*
    module  : unswons.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef UNSWONS_C
#define UNSWONS_C

/**
2130  unswons  :  DAA 	A  ->  R F
R and F are the rest and the first of non-empty aggregate A.
*/
void unswons_lst(void)
{
    value_t temp;
    Stack *list, *quot;

    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    vec_shallow_copy(quot, list);
    temp = vec_pop(quot);
    stack[-1] = MAKE_LIST(quot);
    do_push(temp);
}

void unswons_str(void)
{
    char ch, *str;

    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack[-1]);
    ch = *str++;
    stack[-1] = MAKE_USR_STRING(stringify(str));
    do_push(MAKE_CHAR(ch));
}

void unswons_set(void)
{
    int i;
    uint64_t j, set;

    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            break;
    stack[-1] = MAKE_SET(set & ~j);
    do_push(MAKE_INTEGER(i));
}

void do_unswons(void)
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        unswons_lst();
    else if (IS_USR_STRING(stack[-1]))
        unswons_str();
    else if (IS_SET(stack[-1]))
        unswons_set();
    else
        BADAGGREGATE;
}
#endif
