/*
    module  : times.c
    version : 1.15
    date    : 10/02/23
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK 2800  times  :  DDU	N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    Node node, list;

    PARM(2, TIMES);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node);
    while (node.u.num--)
	exeterm(env, list.u.lis);
}
#endif
