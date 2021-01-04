/*
    module  : opcase.c
    version : 1.14
    date    : 01/04/21
*/
#ifndef OPCASE_C
#define OPCASE_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void do_opcase(void)
{
    int i;
    intptr_t Value;
    Stack *List, *Quot = 0;

    BINARY;
    List = (Stack *)do_pop();
    Value = stack[-1];
    for (i = vec_size(List) - 1; i > 0; i--) {
	Quot = (Stack *)vec_at(List, i);
	if (is_equal_item(Value, vec_back(Quot)))
	    break;
    }
    if (i) {
	vec_copy(List, Quot);
	vec_pop(List);
    } else
	List = (Stack *)vec_at(List, 0);
    do_push((intptr_t)List);
}
#endif
