/*
    module  : unstack.c
    version : 1.12
    date    : 01/19/20
*/
#ifndef UNSTACK_C
#define UNSTACK_C

void lst2stk(Stack *Quot)
{
    int i, j;

    clear_stack();
    for (i = 0, j = vec_size(Quot); i < j; i++)
	do_push(vec_at(Quot, i));
}

/**
unstack  :  [X Y ..]  ->  ..Y X
The list [X Y ..] becomes the new stack.
*/
void do_unstack(void)
{
    SYNCING;
    UNARY;
    lst2stk((Stack *)do_pop());
}
#endif
