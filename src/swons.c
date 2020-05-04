/*
    module  : swons.c
    version : 1.9
    date    : 01/20/20
*/
#ifndef SWONS_C
#define SWONS_C

/**
swons  :  A X  ->  B
Aggregate B is A with a new member X (first member for sequences).
*/
void do_swons(void)
{
    intptr_t Value;
    Stack *Quot = 0;

    BINARY;
    Value = do_pop();
    if (stack[-1])
	vec_copy(Quot, (Stack *)stack[-1]);
    vec_push(Quot, Value);
    stack[-1] = (intptr_t)Quot;
}
#endif
