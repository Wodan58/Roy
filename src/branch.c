/*
    module  : branch.c
    version : 1.12
    date    : 09/19/23
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
    third = lst_pop(env->stck);
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    exeterm(env, first.u.num ? second.u.lis : third.u.lis);
}
#endif
