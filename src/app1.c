/*
    module  : app1.c
    version : 1.12
    date    : 09/19/23
*/
#ifndef APP1_C
#define APP1_C

/**
OK 2440  app1  :  DDA	X [P]  ->  R
Executes P, pushes result R on stack.
*/
void app1_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = lst_pop(env->stck);
    exeterm(env, node.u.lis);
}
#endif
