/*
    module  : branch.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef BRANCH_C
#define BRANCH_C

/**
OK  2590  branch  :  DDDP  B [T] [F]  ->  ...
If B is true, then executes T else executes F.
*/
void branch_(pEnv env)
{
    Node first, second, third;

    PARM(3, WHILE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    exeterm(env, first.u.num ? second.u.lis : third.u.lis);
}
#endif
