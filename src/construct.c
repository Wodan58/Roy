/*
    module  : construct.c
    version : 1.22
    date    : 10/11/24
*/
#ifndef CONSTRUCT_C
#define CONSTRUCT_C

/**
OK  2470  construct  :  DDU  [P] [[P1] [P2] ..]  ->  R1 R2 ..
Saves state of stack and then executes [P].
Then executes each [Pi] to give Ri pushed onto saved stack.
*/
void construct_(pEnv env)
{	/* [P] [[P1] [P2] ..] -> X1 X2 ..	*/
    int i, j;
    Node first, second, node[2], elem, result;

    PARM(2, WHILE);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    /*
	save the old stack; this will become the new stack
    */
    vec_copy_all(node[0].u.lis, env->stck);
    /*
	execute the first program
    */
    exeterm(env, first.u.lis);
    /*
	the new stack after the first program needs to be saved
    */
    vec_copy_all(node[1].u.lis, env->stck);
    /*
	each of the programs in the construct needs to be executed
    */
    vec_init(result.u.lis);
    for (i = vec_size(second.u.lis) - 1; i >= 0; i--) {
	elem = vec_at(second.u.lis, i);
	exeterm(env, elem.u.lis);
	elem = vec_pop(env->stck);
	vec_push(result.u.lis, elem);
	if (i)
	    vec_copy_all(env->stck, node[1].u.lis);
    }
    vec_copy_all(env->stck, node[0].u.lis);
    for (i = 0, j = vec_size(result.u.lis); i < j; i++) {
	elem = vec_at(result.u.lis, i);
	vec_push(env->stck, elem);
    }
}
#endif
