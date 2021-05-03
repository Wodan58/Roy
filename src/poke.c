/*
    module  : poke.c
    version : 1.1
    date    : 04/27/21
*/
#ifndef POKE_C
#define POKE_C

/**
poke  :  X Y Z 2  ->  Z Y
Updates the nth (e.g. 2) item X of the stack with the value on top of the stack.
*/
void do_poke(void)
{
    QUATERN;
    if (stack[-1] < stack_size() - 1) {
	stack[-2 - stack[-1]] = stack[-2];
	stack_pop();
	stack_pop();
    }
}
#endif
