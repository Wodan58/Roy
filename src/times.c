/*
    module  : times.c
    version : 1.18
    date    : 11/12/24
*/
#ifndef TIMES_C
#define TIMES_C

/**
OK  2800  times  :  DDU  N [P]  ->  ...
N times executes P.
*/
void times_(pEnv env)
{
    int64_t i;
    Node list, node;

    PARM(2, TIMES);
    list = vec_pop(env->stck);
    node = vec_pop(env->stck);
    for (i = 0; i < node.u.num; i++)
	exeterm(env, list.u.lis);
}
#endif
