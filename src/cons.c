/*
    module  : cons.c
    version : 1.9
    date    : 01/20/20
*/
#ifndef CONS_C
#define CONS_C

/**
cons  :  X A  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_cons(void)
{
    Stack *List, *Quot = 0;

    BINARY;
    List = (Stack *)do_pop();
    if (List)
	vec_copy(Quot, List);
    vec_push(Quot, stack[-1]);
    stack[-1] = (intptr_t)Quot;
}
#endif
