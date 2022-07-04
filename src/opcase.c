/*
    module  : opcase.c
    version : 1.15
    date    : 06/21/22
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
2100  opcase  :  DA	X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void do_opcase(void)
{
    int i;
    value_t temp;
    Stack *list, *quot, *result = 0;

    TWOPARAMS;
    LIST;
    CHECKEMPTYLIST(stack[-1]);
    list = (Stack *)GET_AS_LIST(stack_pop());
    temp = stack[-1];
    for (i = vec_size(list) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(list, i));
        quot = (Stack *)GET_AS_LIST(vec_at(list, i));
        if (!i || !Compare(temp, vec_back(quot))) {
            if (!i)
                result = quot;
            else {
                vec_shallow_copy(result, quot);
                vec_pop(result);
            }
            break;
        }
    }
    do_push(MAKE_LIST(result));
}
#endif
