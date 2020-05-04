/*
    module  : in.c
    version : 1.11
    date    : 03/15/20
*/
#ifndef IN_C
#define IN_C

/**
in  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in(void)
{
    int i;
    Stack *List;
    char *str, *ptr;

    BINARY;
    List = (Stack *)do_pop();
    if ((str = (char *)stack[-1]) == 0)
	return;
    for (i = vec_size(List) - 1; i >= 0; i--) {
	ptr = (char *)vec_at(List, i);
	if (!strcmp(ptr - 1, str - 1))
	    break;
    }
    stack[-1] = i >= 0;
}
#endif
