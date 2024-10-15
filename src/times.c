/*
    module  : times.c
    version : 1.17
    date    : 10/11/24
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK  2800  times  :  DDU  N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    int i;
    Node list, node;

    PARM(2, TIMES);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    for (i = 0; i < node.u.num; i++)
	exeterm(env, list.u.lis);
}
#endif
