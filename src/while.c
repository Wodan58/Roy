/*
    module  : while.c
    version : 1.20
    date    : 10/02/23
*/
#ifndef WHILE_C
#define WHILE_C

/**
OK 2700  while  :  DDP	[B] [D]  ->  ...
While executing B yields true executes D.
*/
void while_(pEnv env)
{
    Node test, body, node;

    PARM(2, WHILE);
    env->stck = pvec_pop(env->stck, &body);
    env->stck = pvec_pop(env->stck, &test);
    for (;;) {
	exeterm(env, test.u.lis);
	env->stck = pvec_pop(env->stck, &node);
	if (!node.u.num)
	    break;
	exeterm(env, body.u.lis);
    }
}
#endif
