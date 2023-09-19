/*
    module  : iffile.c
    version : 1.10
    date    : 09/19/23
*/
#ifndef IFFILE_C
#define IFFILE_C

/**
OK 2680  iffile  :  DDDP	X [T] [E]  ->  ...
If X is a file, executes T else executes E.
*/
void iffile_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    node = lst_back(env->stck);
    node = node.op == FILE_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
