/*
    module  : while.c
    version : 1.21
    date    : 09/18/24
*/
#ifndef WHILE_C
#define WHILE_C

/**
OK  2700  while  :  DDP  [B] [D]  ->  ...
While executing B yields true executes D.
*/
void while_(pEnv env)
{
    Node body, test, node;

    PARM(2, WHILE);
    body = vec_pop(env->stck);
    test = vec_pop(env->stck);
    for (;;) {
	exeterm(env, test.u.lis);
	node = vec_pop(env->stck);
	if (!node.u.num)
	    break;
	exeterm(env, body.u.lis);
    }
}
#endif
