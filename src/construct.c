/*
    module  : construct.c
    version : 1.18
    date    : 09/19/23
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
    second = lst_pop(env->stck);
    first = lst_pop(env->stck);
    /*
	save the old stack; this will become the new stack
    */
    lst_init(node[0].u.lis);
    lst_copy(node[0].u.lis, env->stck);
    /*
	execute the first program
    */
    exeterm(env, first.u.lis);
    /*
	the new stack after the first program needs to be saved
    */
    lst_init(node[1].u.lis);
    lst_copy(node[1].u.lis, env->stck);
    /*
	each of the programs in the construct needs to be executed
    */
    lst_init(result.u.lis);
    for (i = lst_size(second.u.lis) - 1; i >= 0; i--) {
	elem = lst_at(second.u.lis, i);
	exeterm(env, elem.u.lis);
	elem = lst_pop(env->stck);
	lst_push(result.u.lis, elem);
	if (i)
	    lst_copy(env->stck, node[1].u.lis);
    }
    lst_copy(env->stck, node[0].u.lis);
    for (i = 0, j = lst_size(result.u.lis); i < j; i++) {
	elem = lst_at(result.u.lis, i);
	lst_push(env->stck, elem);
    }
}
#endif
