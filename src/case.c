/*
    module  : case.c
    version : 1.19
    date    : 06/21/22
*/
#ifndef CASE_C
#define CASE_C

/**
2110  case  :  DDU	X [..[X Y]..]  ->  [Y] i
Indexing on the value of X, execute the matching Y.
*/
void exe_case(Stack *list)
{
    int i;
    Stack *quot, *result = 0;

    ONEPARAM;
    for (i = vec_size(list) - 1; i >= 0; i--) {
        CHECKLIST(vec_at(list, i));
        quot = (Stack *)GET_AS_LIST(vec_at(list, i));
        if (!i || !Compare(stack[-1], vec_back(quot))) {
            if (!i)
                result = quot;
            else {
                vec_shallow_copy(result, quot);
                vec_pop(result);
                stack_pop();
            }
            break;
        }
    }
    execute(result);
}

#ifdef COMPILING
void put_case(Stack *list)
{
    int i;
    Stack *quot, *result;

    fprintf(program, "{ int num = 0; do {");
    for (i = vec_size(list) - 1; i > 0; i--) {
        CHECKLIST(vec_at(list, i));
        quot = (Stack *)GET_AS_LIST(vec_at(list, i));
        printvalue(vec_back(quot));
        fprintf(program, "if (!Compare(stack[-2], stack[-1])) {");
        fprintf(program, "stack_pop(); stack_pop();");
        vec_shallow_copy(result, quot);
        vec_pop(result);
        compile(result);
        fprintf(program, "num = 1; break; } stack_pop();");
    }
    fprintf(program, "break; } while(0); if (!num) {");
    CHECKLIST(vec_at(list, 0));
    compile((Stack *)GET_AS_LIST(vec_at(list, 0)));
    fprintf(program, "} }");
}
#endif

void do_case(void)
{
    Stack *prog;

    ONEPARAM;
    LIST;
    CHECKEMPTYLIST(stack[-1]);
    prog = (Stack *)GET_AS_LIST(stack_pop());
    INSTANT(put_case);
    exe_case(prog);
}
#endif
