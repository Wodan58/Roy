/*
    module  : infra.c
    version : 1.21
    date    : 10/11/24
*/
#ifndef INFRA_C
#define INFRA_C

/**
OK  2810  infra  :  DDA  L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void infra_(pEnv env)
{
    Node prog, aggr, node;

    PARM(2, INFRA);
    prog = vec_pop(env->stck);			/* program to execute */
    aggr = vec_pop(env->stck);			/* stack to use */
    vec_copy_all(node.u.lis, env->stck); 	/* save stack */
    vec_copy_all(env->stck, aggr.u.lis); 	/* new stack */
    exeterm(env, prog.u.lis);			/* execute program */
    vec_copy_all(prog.u.lis, env->stck); 	/* copy stack */
    vec_copy_all(env->stck, node.u.lis); 	/* old stack */
    vec_push(env->stck, prog);			/* push the calculated list */
}
#endif
