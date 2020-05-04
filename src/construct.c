/*
    module  : construct.c
    version : 1.15
    date    : 01/20/20
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

void construct(Stack *prog[])
{
    int i;
    Stack *save[2], *result = 0;

    save[0] = stk2lst();
    execute(prog[0]);
    for (i = vec_size(prog[1]) - 1; i >= 0; i--) {
	save[1] = stk2lst();
	execute((Stack *)vec_at(prog[1], i));
	vec_push(result, do_pop());
	lst2stk(save[1]);
    }
    lst2stk(save[0]);
    for (i = vec_size(result) - 1; i >= 0; i--)
	do_push(vec_at(result, i));
}

#ifdef COMPILING
void put_construct(Stack *prog[])
{
    int i;

    fprintf(program, "{ int i; Stack *save[2], *result = 0;");
    fprintf(program, "save[0] = stk2lst();");
    execute(prog[0]);
    for (i = vec_size(prog[1]) - 1; i >= 0; i--) {
        fprintf(program, "save[1] = stk2lst();");
	clear_stack();
        execute((Stack *)vec_at(prog[1], i));
        fprintf(program, "vec_push(result, do_pop()); lst2stk(save[1]);");
    }
    fprintf(program, "lst2stk(save[0]); for (i = vec_size(result) - 1;");
    fprintf(program, "i >= 0; i--) do_push(vec_at(result, i)); }");
}
#endif

/**
construct  :  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
void do_construct(void)
{
    Stack *prog[2];

    BINARY;
    prog[1] = (Stack *)do_pop();
    prog[0] = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_construct(prog);
    else
#endif
    construct(prog);
}
#endif
