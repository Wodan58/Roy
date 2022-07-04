/*
    module  : small.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef SMALL_C
#define SMALL_C

/**
2220  small  :  DA	X  ->  B
Tests whether aggregate X has 0 or 1 members, or numeric 0 or 1.
*/
void small_str(void)
{
    char *str;

    str = get_string(stack[-1]);
    stack[-1] = MAKE_BOOLEAN(strlen(str) < 2);
}

void small_set(void)
{
    int i, k = 0;
    uint64_t j, set;

    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            k++;
    stack[-1] = MAKE_BOOLEAN(k < 2);
}

void do_small(void)
{
    ONEPARAM;
    if (IS_INTEGER(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(GET_AS_INTEGER(stack[-1]) < 2);
    else if (IS_LIST(stack[-1]))
        stack[-1] = MAKE_BOOLEAN(vec_size((Stack *)GET_AS_LIST(stack[-1])) < 2);
    else if (IS_USR_STRING(stack[-1]))
        small_str();
    else if (IS_SET(stack[-1]))
        small_set();
    else
        BADDATA;
}
#endif
