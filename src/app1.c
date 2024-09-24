/*
    module  : app1.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef APP1_C
#define APP1_C

/**
OK  2440  app1  :  DDA  X [P]  ->  R
Executes P, pushes result R on stack.
*/
void app1_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = vec_pop(env->stck);
    exeterm(env, node.u.lis);
}
#endif
