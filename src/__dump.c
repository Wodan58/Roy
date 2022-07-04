/*
    module  : __dump.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef _LOWBAR__LOWBAR_DUMP_C
#define _LOWBAR__LOWBAR_DUMP_C

/**
1070  __dump  :  A	->  [..]
debugging only: pushes the dump as a list.
*/
void do__lowbar__lowbar_dump(void)
{
    Stack *list;

    COMPILE;
    vec_init(list);
    do_push(MAKE_LIST(list));
}
#endif
