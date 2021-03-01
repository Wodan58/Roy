/*
    module  : case.c
    version : 1.18
    date    : 03/01/21
*/
#ifndef CASE_C
#define CASE_C

#ifdef EQUAL_X
#undef EQUAL_X
#undef EQUAL_C
#endif

#include "equal.c"

void my_case(Stack *list)
{
    int i;
    intptr_t First;
    Stack *quot, *next;

    First = stack[-1];
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	if (is_equal_item(First, vec_back(quot))) {
	    do_pop();
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
    intptr_t Second;
    Stack *quot, *next;

    fprintf(program, "{ int num = 0; intptr_t First = stack[-1]; do {");
    for (i = vec_size(list) - 1; i > 0; i--) {
	quot = (Stack *)vec_at(list, i);
	Second = vec_back(quot);
	if (is_usr(Second) || is_string(Second)) {
	    fprintf(program, "if (!strcmp((char *)First, ");
	    writestring(program, (char *)Second);
	} else
	    fprintf(program, "if (stack[-1] == %" PRIdPTR "", Second);
	fprintf(program, ") { do_pop();");
	vec_copy(next, quot);
	vec_pop(next);
	execute(next);
	fprintf(program, "num = 1; break; }");
    }
    fprintf(program, "break; } while(0); if (!num) {");
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
    if (compiling && STACK(1))
	put_case(list);
    else
#endif
    my_case(list);
}
#endif
