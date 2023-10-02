/*
    module  : ifchar.c
    version : 1.11
    date    : 10/02/23
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
OK 2620  ifchar  :  DDDP	X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    node = pvec_lst(env->stck);
    node = node.op == CHAR_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
