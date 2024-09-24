/*
    module  : dip.c
    version : 1.16
    date    : 09/18/24
*/
#ifndef DIP_C
#define DIP_C

/**
OK  2430  dip  :  DDAP  X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
void dip_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    exeterm(env, list.u.lis);
    vec_push(env->stck, node);
}
#endif
