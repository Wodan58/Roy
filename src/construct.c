/*
    module  : construct.c
    version : 1.20
    date    : 10/12/23
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

/**
OK 2470  construct  :  DDU 	[P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
PRIVATE void construct_(pEnv env)
{	/* [P] [[P1] [P2] ..] -> X1 X2 ..	*/
    int i, j;
    Node first, second, node[2], elem, result;

    PARM(2, WHILE);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    /*
	save the old stack; this will become the new stack
    */
    node[0].u.lis = pvec_init();
    pvec_copy(node[0].u.lis, env->stck);
    /*
	execute the first program
    */
    exeterm(env, first.u.lis);
    /*
	the new stack after the first program needs to be saved
    */
    node[1].u.lis = pvec_init();
    pvec_copy(node[1].u.lis, env->stck);
    /*
	each of the programs in the construct needs to be executed
    */
    result.u.lis = pvec_init();
    for (i = pvec_cnt(second.u.lis) - 1; i >= 0; i--) {
	elem = pvec_nth(second.u.lis, i);
	exeterm(env, elem.u.lis);
	env->stck = pvec_pop(env->stck, &elem);
	result.u.lis = pvec_add(result.u.lis, elem);
	if (i)
	    pvec_copy(env->stck, node[1].u.lis);
    }
    pvec_copy(env->stck, node[0].u.lis);
    for (i = 0, j = pvec_cnt(result.u.lis); i < j; i++) {
	elem = pvec_nth(result.u.lis, i);
	env->stck = pvec_add(env->stck, elem);
    }
}
#endif
