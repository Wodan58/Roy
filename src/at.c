/*
    module  : at.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef AT_C
#define AT_C

/**
2070  at  :  DDA	A I  ->  X
X (= A[I]) is the member of A at position I.
*/
void at_lst(void)
{
    int index;
    Stack *list;

    index = GET_AS_INTEGER(stack_pop());
    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack[-1]);
    index = vec_size(list) - 1 - index;
    if (index < 0 || index >= vec_size(list))
        INDEXTOOLARGE;
    stack[-1] = vec_at(list, index);
}

void at_str(void)
{
    int index;
    char *str;

    index = GET_AS_INTEGER(stack_pop());
    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack[-1]);
    if (index < 0 || index >= strlen(str))
        INDEXTOOLARGE;
    stack[-1] = MAKE_CHAR(str[index]);
}

void at_set(void)
{
    uint64_t set;
    int i, index;

    index = GET_AS_INTEGER(stack_pop());
    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack[-1]);
    for (i = 0; i < SETSIZE_; i++)
        if (set & ((uint64_t)1 << i)) {
            if (!index) {
                stack[-1] = MAKE_INTEGER(i);
                return;
            }
            index--;
        }
    INDEXTOOLARGE;
}

void do_at(void)
{
    TWOPARAMS;
    INTEGER;
    if (IS_LIST(stack[-2]))
        at_lst();
    else if (IS_USR_STRING(stack[-2]))
        at_str();
    else if (IS_SET(stack[-2]))
        at_set();
    else
        BADAGGREGATE;
}
#endif
