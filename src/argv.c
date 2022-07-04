/*
    module  : argv.c
    version : 1.14
    date    : 06/21/22
*/
#ifndef ARGV_C
#define ARGV_C

/**
3060  argv  :  A	->  A
Creates an aggregate A containing the interpreter's command line arguments.
*/
void do_argv(void)
{
    int i;
    Stack *list;

    COMPILE;
    vec_init(list);
    for (i = g_argc - 1; i >= 0; i--)
        vec_push(list, MAKE_USR_STRING(stringify(g_argv[i])));
    do_push(MAKE_LIST(list));
}
#endif
