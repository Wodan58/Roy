/*
    module  : of.c
    version : 1.9
    date    : 06/21/22
*/
#ifndef OF_C
#define OF_C

/**
2080  of  :  DDA	I A  ->  X
X (= A[I]) is the I-th member of aggregate A.
*/
void of_lst(void)
{
    int index;
    Stack *quot;

    CHECKEMPTYLIST(stack[-1]);
    quot = (Stack *)GET_AS_LIST(stack_pop());
    INTEGER;
    index = vec_size(quot) - 1 - GET_AS_INTEGER(stack[-1]);
    if (index < 0 || index >= vec_size(quot))
        INDEXTOOLARGE;
    stack[-1] = vec_at(quot, index);
}

void of_str(void)
{
    int index;
    char *str;

    CHECKEMPTYSTRING(stack[-1]);
    str = get_string(stack_pop());
    INTEGER;
    index = GET_AS_INTEGER(stack[-1]);
    if (index < 0 || index >= strlen(str))
        INDEXTOOLARGE;
    stack[-1] = MAKE_CHAR(str[index]);
}

void of_set(void)
{
    uint64_t set;
    int i, index;

    CHECKEMPTYSET(stack[-1]);
    set = GET_AS_SET(stack_pop());
    INTEGER;
    index = GET_AS_INTEGER(stack[-1]);
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

void do_of(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-1]))
        of_lst();
    else if (IS_USR_STRING(stack[-1]))
        of_str();
    else if (IS_SET(stack[-1]))
        of_set();
    else
        BADAGGREGATE;
}
#endif
