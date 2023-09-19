/*
    module  : while.c
    version : 1.19
    date    : 09/19/23
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
    body = lst_pop(env->stck);
    test = lst_pop(env->stck);
    for (;;) {
	exeterm(env, test.u.lis);
	node = lst_pop(env->stck);
	if (!node.u.num)
	    break;
	exeterm(env, body.u.lis);
    }
}
#endif
