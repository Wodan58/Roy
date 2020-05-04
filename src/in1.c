/*
    module  : in1.c
    version : 1.8
    date    : 03/15/20
*/
#ifndef IN1_C
#define IN1_C

/**
in1  :  X A  ->  B
Tests whether X is a member of aggregate A.
*/
void do_in1(void)
{
    int i, j;
    Stack *List;
    intptr_t Value;
    char *str, *ptr;

    BINARY;
    List = (Stack *)do_pop();
    Value = stack[-1];
    if ((j = is_string(Value)) != 0)
	str = (char *)Value;
    for (i = vec_size(List) - 1; i >= 0; i--)
	if (j) {
	    ptr = (char *)vec_at(List, i);
	    if (!strcmp(ptr - 1, str - 1))
		break;
	} else if (vec_at(List, i) == Value)
	    break;
    stack[-1] = i >= 0;
}
#endif
