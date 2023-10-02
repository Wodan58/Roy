/*
    module  : branch.c
    version : 1.13
    date    : 10/02/23
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
OK 2590  branch  :  DDDP	B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void branch_(pEnv env)
{
    Node first, second, third;

    PARM(3, WHILE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &third);
    exeterm(env, first.u.num ? second.u.lis : third.u.lis);
}
#endif
