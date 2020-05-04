/*
    module  : has.c
    version : 1.9
    date    : 01/19/20
*/
#ifndef HAS_C
#define HAS_C

/**
has  :  A X  ->  B
Tests whether aggregate A has X as a member.
*/
void do_has(void)
{
    int i;
    Stack *List;
    char *str, *ptr;

    BINARY;
    if ((str = (char *)do_pop()) == 0)
	stack[-1] = 0;
    List = (Stack *)stack[-1];
    for (i = vec_size(List) - 1; i >= 0; i--) {
	ptr = (char *)vec_at(List, i);
	if (!strcmp(ptr - 1, str - 1))
	    break;
    }
    stack[-1] = i >= 0;
}
#endif
