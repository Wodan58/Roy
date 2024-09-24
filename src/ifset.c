/*
    module  : ifset.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef IFSET_C
#define IFSET_C

/**
OK  2640  ifset  :  DDDP  X [T] [E]  ->  ...
If X is a set, executes T else executes E.
*/
void ifset_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == SET_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
