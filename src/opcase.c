/*
    module  : opcase.c
    version : 1.12
    date    : 01/20/20
*/
#ifndef OPCASE_C
#define OPCASE_C

/**
opcase  :  X [..[X Xs]..]  ->  X [Xs]
Indexing on type of X, returns the list [Xs].
*/
void do_opcase(void)
{
    int i, j;
    intptr_t Value;
    char *str, *ptr;
    Stack *List, *Quot = 0;

    BINARY;
    List = (Stack *)do_pop();
    Value = stack[-1];
    if ((j = is_string(Value)) != 0)
	str = (char *)Value;
    for (i = vec_size(List) - 1; i > 0; i--) {
	Quot = (Stack *)vec_at(List, i);
	if (j) {
	    if ((ptr = (char *)vec_back(Quot)) != 0)
		if (!strcmp(ptr - 1, str - 1))
		    break;
	} else if (vec_back(Quot) == Value)
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
