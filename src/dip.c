/*
    module  : dip.c
    version : 1.15
    date    : 10/02/23
*/
#ifndef DIP_C
#define DIP_C

/**
OK 2430  dip  :  DDAP	X [P]  ->  ...  X
Saves X, executes P, pushes X back.
*/
PRIVATE void dip_(pEnv env)
{
    Node list, node;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);
    exeterm(env, list.u.lis);
    env->stck = pvec_add(env->stck, node);
}
#endif
