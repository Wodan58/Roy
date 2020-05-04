/*
    module  : dip.c
    version : 1.11
    date    : 01/19/20
*/
#ifndef DIP_C
#define DIP_C

void dip(Stack *Prog)
{
    intptr_t Value;

    Value = do_pop();
    execute(Prog);
    do_push(Value);
}

#ifdef COMPILING
void put_dip(Stack *Prog)
{
    fprintf(program, "{ intptr_t Value = do_pop();");
    execute(Prog);
    fprintf(program, "do_push(Value); }");
}
#endif

/**
dip  :  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
void do_dip(void)
{
    Stack *Prog;

    UNARY;
    Prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_dip(Prog);
    else
#endif
    dip(Prog);
}
#endif
