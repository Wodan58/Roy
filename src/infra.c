/*
    module  : infra.c
    version : 1.19
    date    : 10/02/23
*/
#ifndef INFRA_C
#define INFRA_C

/**
OK 2810  infra  :  DDA	L1 [P]  ->  L2
Using list L1 as stack, executes P and returns a new list L2.
The first element of L1 is used as the top of stack,
and after execution of P the top of stack becomes the first element of L2.
*/
void infra_(pEnv env)
{
    Node aggr, prog, node;

    PARM(2, INFRA);
    env->stck = pvec_pop(env->stck, &prog);	/* program to execute */
    env->stck = pvec_pop(env->stck, &aggr);	/* stack to use */
    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);		/* stack is saved in node */
    pvec_copy(env->stck, aggr.u.lis);		/* stack that will be used */
    exeterm(env, prog.u.lis);			/* execute program */
    prog.u.lis = pvec_init();
    pvec_copy(prog.u.lis, env->stck);		/* copy the stack to a list */
    pvec_copy(env->stck, node.u.lis);		/* restore the old stack */
    env->stck = pvec_add(env->stck, prog);	/* push the calculated list */
}
#endif
