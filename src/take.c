/*
    module  : take.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef TAKE_C
#define TAKE_C

/**
2150  take  :  DDA	A N  ->  B
Aggregate B is the result of retaining just the first N elements of A.
*/
void take_lst(void)
{
    int i, num, leng;
    Stack *list, *result = 0;

    num = GET_AS_INTEGER(stack_pop());
    list = (Stack *)GET_AS_LIST(stack[-1]);
    leng = vec_size(list);
    if (num < 0 || num >= leng)
        INDEXTOOLARGE;
    for (i = leng - num; i < leng; i++)
        vec_push(result, vec_at(list, i));
    stack[-1] = MAKE_LIST(result);
}

void take_str(void)
{
    int num;
    char *ptr, *str;

    num = GET_AS_INTEGER(stack_pop());
    ptr = get_string(stack[-1]);
    if (num < 0 || num >= strlen(ptr))
	INDEXTOOLARGE;
    str = GC_malloc_atomic(num + 2);
    *str = '"';
    strncpy(str + 1, ptr, num);
    str[num + 1] = 0;
    stack[-1] = MAKE_USR_STRING(str);
}

void take_set(void)
{
    int i, num;
    uint64_t j, set, result = 0;

    num = GET_AS_INTEGER(stack_pop());
    if (num < 0 || num >= SETSIZE_)
	INDEXTOOLARGE;
    set = GET_AS_SET(stack[-1]);
    for (i = 0, j = 1; i < SETSIZE_ && num; i++, j <<= 1)
        if (set & j) {
            result |= j;
            num--;
        }
    stack[-1] = MAKE_SET(result);
}

void do_take(void)
{
    TWOPARAMS;
    if (IS_LIST(stack[-2]))
        take_lst();
    else if (IS_USR_STRING(stack[-2]))
        take_str();
    else if (IS_SET(stack[-2]))
        take_set();
    else
        BADAGGREGATE;
}
#endif
