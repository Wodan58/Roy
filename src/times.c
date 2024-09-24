/*
    module  : times.c
    version : 1.16
    date    : 09/18/24
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK  2800  times  :  DDU  N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    Node list, node;

    PARM(2, TIMES);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    while (node.u.num--)
	exeterm(env, list.u.lis);
}
#endif
