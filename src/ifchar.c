/*
    module  : ifchar.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef IFCHAR_C
#define IFCHAR_C

/**
OK  2620  ifchar  :  DDDP  X [T] [E]  ->  ...
If X is a character, executes T else executes E.
*/
void ifchar_(pEnv env)
{
    Node first, second, node;

    PARM(3, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    node = vec_back(env->stck);
    node = node.op == CHAR_ ? first : second;
    exeterm(env, node.u.lis);
}
#endif
