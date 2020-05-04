/*
    module  : all_str.c
    version : 1.1
    date    : 03/15/20
*/
#ifndef ALL_STR_C
#define ALL_STR_C

void all_str(Stack *prog)
{
    char *str;
    intptr_t num = 1;

    str = (char *)do_pop();
    for (; str && *str; str++) {
	do_push(*str);
	execute(prog);
	num = do_pop();
	do_zap();
	if (!num)
	    break;
    }
    do_push(num);
}

#ifdef COMPILING
void put_all_str(Stack *prog)
{
    fprintf(program, "{ char *str; intptr_t num = 1;");
    fprintf(program, "str = (char *)do_pop();");
    fprintf(program, "for (; str && *str; str++) {");
    fprintf(program, "do_push(*str);");
    execute(prog);
    fprintf(program, "num = do_pop(); do_zap();");
    fprintf(program, "if (!num) break; }");
    fprintf(program, "do_push(num); }");
}
#endif

/**
all_str  :  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void do_all_str(void)
{
    Stack *prog;

    UNARY;
    prog = (Stack *)do_pop();
#ifdef COMPILING
    if (compiling && stack_empty())
	put_all_str(prog);
    else
#endif
    all_str(prog);
}
#endif
