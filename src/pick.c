/*
    module  : pick.c
    version : 1.6
    date    : 01/19/20
*/
#ifndef PICK_C
#define PICK_C

/**
pick  :  X Y Z 2  ->  X Y Z X
Pushes an extra copy of nth (e.g. 2) item X on top of the stack.
*/
void do_pick(void)
{
    QUATERN;
    if (stack[-1] < stack_size() - 1)
	stack[-1] = stack[-2 - stack[-1]];
    else
	stack[-1] = 1;
}
#endif
