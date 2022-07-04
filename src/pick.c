/*
    module  : pick.c
    version : 1.7
    date    : 06/21/22
*/
#ifndef PICK_C
#define PICK_C

/**
3230  pick  :  A	X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void do_pick(void)
{
    int num;

    FOURPARAMS;
    if ((num = GET_AS_INTEGER(stack[-1])) < stack_size() - 1)
        stack[-1] = stack[-2 - num];
}
#endif
