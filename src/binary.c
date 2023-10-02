/*
    module  : binary.c
    version : 1.11
    date    : 10/02/23
*/
#ifndef BINARY_C
#define BINARY_C

/**
OK 2560  binary  :  DDDA	X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
void binary_(pEnv env)
{
    Node node, list;

    PARM(3, DIP);
    env->stck = pvec_pop(env->stck, &list);
    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);		/* stack is saved in node */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &list);	/* take R from stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove Y from old stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove X from old stack */
    node.u.lis = pvec_add(node.u.lis, list);	/* add R to old stack */
    pvec_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
