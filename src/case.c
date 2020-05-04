/*
    module  : case.c
    version : 1.15
    date    : 01/20/20
*/
#ifndef CASE_C
#define CASE_C

void my_case(Stack *list)
{
    int i;
    Stack *quot, *next;
    intptr_t First, Second;

    First = stack[-1];
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	Second = vec_back(quot);
	if (is_string(First) && is_string(Second)) {
	    if (!strcmp((char *)First, (char *)Second)) {
		do_zap();
		break;
	    }
	} else if (First == Second) {
	    do_zap();
	    break;
	}
    }
    if (i) {
	vec_copy(next, quot);
	vec_pop(next);
    } else
	next = (Stack *)vec_at(list, 0);
    execute(next);
}

#ifdef COMPILING
void put_case(Stack *list)
{
    int i;
    Stack *quot, *next;

    fprintf(program, "{ int num = 0; for (;;) {");
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	fprintf(program, "if (stack[-1] == %" PRIdPTR ") { do_zap();",
		vec_back(quot));
	vec_copy(next, quot);
	vec_pop(next);
	execute(next);
	fprintf(program, "num = 1; break; }");
    }
    fprintf(program, "break; } if (!num) {");
    execute((Stack *)vec_at(list, 0));
    fprintf(program, "} }");
}
#endif

/**
case  :  X [..[X Y]..]  ->  [Y] i
Indexing on the value of X, execute the matching Y.
*/
void do_case(void)
{
    Stack *list;

    UNARY;
    list = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_case(list);
    else
#endif
    my_case(list);
}
#endif
