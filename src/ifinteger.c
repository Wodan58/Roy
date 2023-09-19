/*
    module  : ifinteger.c
    version : 1.10
    date    : 09/19/23
*/
#ifndef IFINTEGER_C
#define IFINTEGER_C

/**
OK 2610  ifinteger  :  DDDP	X [T] [E]  ->  ...
If X is an integer, executes T else executes E.
*/
void ifinteger_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == INTEGER_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
