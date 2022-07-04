/*
    module  : drop.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef DROP_C
#define DROP_C

/**
2140  drop  :  DDA	A N  ->  B
Aggregate B is the result of deleting the first N elements of A.
*/
void drop_lst(void)
{
    int num, size;
    Stack *list, *quot;

    num = GET_AS_INTEGER(stack_pop());
    quot = (Stack *)GET_AS_LIST(stack[-1]);
    size = vec_size(quot);
    if (num < 0 || num >= size)
	INDEXTOOLARGE;
    vec_shallow_copy(list, quot);
    vec_setsize(list, size - num);
    stack[-1] = MAKE_LIST(list);
}

void drop_str(void)
{
    int num;
    char *str;

    num = GET_AS_INTEGER(stack_pop());
    str = get_string(stack[-1]);
    if (num < 0 || num >= strlen(str))
	INDEXTOOLARGE;
    while (num-- > 0 && *str)
        str++;
    stack[-1] = MAKE_USR_STRING(stringify(str));
}

void drop_set(void)
{
    int i, num;
    uint64_t set, j;

    num = GET_AS_INTEGER(stack_pop());
    if (num < 0 || num >= SETSIZE_)
	INDEXTOOLARGE;
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_ && num; i++, j <<= 1)
        if (set & j) {
            set &= ~j;
            num--;
        }
    stack[-1] = MAKE_SET(set);
}

void do_drop(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-2]))
        drop_lst();
    else if (IS_USR_STRING(stack[-2]))
        drop_str();
    else if (IS_SET(stack[-2]))
        drop_set();
    else
        BADAGGREGATE;
}
#endif
