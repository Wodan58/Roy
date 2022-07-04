/*
    module  : __manual_list.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_MANUAL_LOWBAR_LIST_C
#define _LOWBAR__LOWBAR_MANUAL_LOWBAR_LIST_C

/**
2980  __manual_list  :  A	->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
void do__lowbar__lowbar_manual_lowbar_list(void)
{
#ifdef COMPILING
    int i;
    Stack *list = 0, *quot;

    for (i = 0; optable[i].name; i++)
        ;
    while (--i) {
        quot = 0;
        vec_push(quot, MAKE_USR_STRING(stringify(optable[i].messg2)));
        vec_push(quot, MAKE_USR_STRING(stringify(optable[i].messg1)));
        vec_push(quot, MAKE_USR_STRING(stringify(optable[i].name)));
        vec_push(list, MAKE_LIST(quot));
    }
    do_push(MAKE_LIST(list));
#endif
}
#endif
