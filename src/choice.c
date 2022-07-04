/*
    module  : choice.c
    version : 1.12
    date    : 06/21/22
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
1330  choice  :  DDDA 	B T F  ->  X
If B is true, then X = T else X = F.
*/
void do_choice(void)
{
    THREEPARAMS;
    stack[-3] = GET_AS_BOOLEAN(stack[-3]) ? stack[-2] : stack[-1];
    stack_pop();
    stack_pop();
}
#endif
