/*
    module  : body.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef BODY_C
#define BODY_C

/**
2200  body  :  DA	U  ->  [P]
Quotation [P] is the body of user-defined symbol U.
*/
void do_body(void)
{
#ifdef COMPILING
    Stack *list;

    ONEPARAM;
    USERDEF;
    if (IS_USR_INDEX(stack[-1]))
        stack[-1] = locate(GET_AS_USR_INDEX(stack[-1]));
    else {
        vec_init(list);
        stack[-1] = MAKE_LIST(list);
    }
#else
    ONEPARAM;
    stack_pop();
#endif
}
#endif
