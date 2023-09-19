/*
    module  : infra.c
    version : 1.18
    date    : 09/19/23
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
    prog = lst_pop(env->stck);		/* program to execute */
    aggr = lst_pop(env->stck);		/* stack to use */
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);	/* stack is saved in node */
    lst_copy(env->stck, aggr.u.lis);	/* stack that will be used */
    exeterm(env, prog.u.lis);		/* execute program */
    lst_init(prog.u.lis);
    lst_copy(prog.u.lis, env->stck);	/* copy the stack to a list */
    lst_copy(env->stck, node.u.lis);	/* restore the old stack */
    lst_push(env->stck, prog);		/* push the calculated list */
}
#endif
