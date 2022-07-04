/*
    module  : conts.c
    version : 1.10
    date    : 06/21/22
*/
#ifndef CONTS_C
#define CONTS_C

/**
1080  conts  :  A	->  [[P] [Q] ..]
Pushes current continuations. Buggy, do not use.
*/
void do_conts(void)
{
    Stack *list;

    vec_init(list);
    do_push(MAKE_LIST(list));
}
#endif
