/*
    module  : iffloat.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef IFFLOAT_C
#define IFFLOAT_C

/**
OK  2670  iffloat  :  DDDP  X [T] [E]  ->  ...
If X is a float, executes T else executes E.
*/
void iffloat_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == FLOAT_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
