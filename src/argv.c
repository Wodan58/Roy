/*
    module  : argv.c
    version : 1.13
    date    : 01/20/20
*/
#ifndef ARGV_C
#define ARGV_C

/**
argv  :  ->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
void do_argv(void)
{
    int i;
    Stack *List = 0;

    COMPILE;
    for (i = g_argc - 1; i >= 0; i--)
	vec_push(List, (intptr_t)g_argv[i]);
    do_push((intptr_t)List);
}
#endif
