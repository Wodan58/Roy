/*
    module  : construct.c
    version : 1.17
    date    : 06/21/22
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

/**
2490  construct  :  DDU 	[P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
void construct(Stack *prog[2])
{
    int i, j;
    Stack *save[2], *result = 0;

    save[0] = stack_copy();
    execute(prog[0]);
    save[1] = stack_copy();
    for (i = vec_size(prog[1]) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(prog[1], i));
        execute((Stack *)GET_AS_LIST(vec_at(prog[1], i)));
        vec_push(result, stack_pop());
        if (i)
            stack_from_list(save[1]);
    }
    stack_from_list(save[0]);
    for (i = 0, j = vec_size(result); i < j; i++)
        do_push(vec_at(result, i));
}

#ifdef COMPILING
void put_construct(Stack *prog[2])
{
    int i;

    fprintf(program, "{ int i, j; Stack *save[2], *result = 0;");
    fprintf(program, "save[0] = stack_copy();");
    compile(prog[0]);
    fprintf(program, "save[1] = stack_copy();");
    for (i = vec_size(prog[1]) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(prog[1], i));
        compile((Stack *)GET_AS_LIST(vec_at(prog[1], i)));
        fprintf(program, "vec_push(result, stack_pop());");
        if (i)
            fprintf(program, "stack_from_list(save[1]);");
    }
    fprintf(program, "stack_from_list(save[0]);");
    fprintf(program, "for (i = 0, j = vec_size(result); i < j; i++)");
    fprintf(program, "do_push(vec_at(result, i)); }");
}
#endif

void do_construct(void)
{
    Stack *prog[2];

    TWOPARAMS;
    TWOQUOTES;
    prog[1] = (Stack *)GET_AS_LIST(stack_pop());
    prog[0] = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_construct);
    construct(prog);
}
#endif
