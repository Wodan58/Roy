/*
    module  : choice.c
    version : 1.11
    date    : 07/23/20
*/
#ifndef CHOICE_C
#define CHOICE_C

/**
choice  :  B T F  ->  X
If B is true, then X = T else X = F.
*/
void do_choice(void)
{
    TERNARY;
    stack[-3] = stack[-3] ? stack[-2] : stack[-1];
    do_pop();
    do_pop();
}
#endif
