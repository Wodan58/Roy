/*
    module  : size.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef SIZE_C
#define SIZE_C

/**
2090  size  :  DA	A  ->  I
Integer I is the number of elements of aggregate A.
*/
void size_str(void)
{
    stack[-1] = MAKE_INTEGER(strlen(get_string(stack[-1])));
}

void size_set(void)
{
    int i, k = 0;
    uint64_t j, set;

    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_; i++, j <<= 1)
        if (set & j)
            k++;
    stack[-1] = MAKE_INTEGER(k);
}

void do_size(void)
{
    ONEPARAM;
    if (IS_LIST(stack[-1]))
        stack[-1] = MAKE_INTEGER(vec_size((Stack *)GET_AS_LIST(stack[-1])));
    else if (IS_USR_STRING(stack[-1]))
        size_str();
    else if (IS_SET(stack[-1]))
        size_set();
    else
        BADAGGREGATE;
}
#endif
