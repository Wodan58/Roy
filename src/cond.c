/*
    module  : cond.c
    version : 1.19
    date    : 06/21/22
*/
#ifndef COND_C
#define COND_C

/**
2710  cond  :  DU	[..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void cond(Stack *prog)
{
    int i;
    Stack *quot, *list, *result = 0;

    for (i = vec_size(prog) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(prog, i));
        quot = (Stack *)GET_AS_LIST(vec_at(prog, i));
        if (!i) {
            result = quot;
            break;
        }
        CHECKLIST(vec_back(quot));
        execute_cond((Stack *)GET_AS_LIST(vec_back(quot)), 0);
        CHECKSTACK;
        if (GET_AS_BOOLEAN(stack_pop())) {
            vec_shallow_copy(result, quot);
            vec_pop(result);
            break;
        }
    }
    execute(result);
}

#ifdef COMPILING
void put_cond(Stack *prog)
{
    int i;
    Stack *quot, *result;

    fprintf(program, "{ int num = 0; for (;;) {");
    for (i = vec_size(prog) - 1; i > 0; i--) {
        CHECKLIST(vec_at(prog, i));
        quot = (Stack *)GET_AS_LIST(vec_at(prog, i));
        CHECKLIST(vec_back(quot));
        compile_cond((Stack *)GET_AS_LIST(vec_back(quot)), 0);
        fprintf(program, "num = GET_AS_BOOLEAN(stack_pop());");
        fprintf(program, "if (num) {");
        vec_shallow_copy(result, quot);
        vec_pop(result);
        compile(result);
        fprintf(program, "break; }");
    }
    fprintf(program, "break; } if (!num) {");
    CHECKLIST(vec_at(prog, 0));
    compile((Stack *)GET_AS_LIST(vec_at(prog, 0)));
    fprintf(program, "} }");
}
#endif

void do_cond(void)
{
    Stack *prog;

    ONEPARAM;
    LIST;
    CHECKEMPTYLIST(stack[-1]);
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_cond);
    cond(prog);
}
#endif
