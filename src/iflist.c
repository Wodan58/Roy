/*
    module  : iflist.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef IFLIST_C
#define IFLIST_C

/**
OK  2660  iflist  :  DDDP  X [T] [E]  ->  ...
If X is a list, executes T else executes E.
*/
void iflist_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == LIST_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
