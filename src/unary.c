/*
    module  : unary.c
    version : 1.12
    date    : 10/02/23
*/
#ifndef UNARY_C
#define UNARY_C

/**
OK 2490  unary  :  DDA	X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void unary_(pEnv env)
{
    Node node, list;

    PARM(2, DIP);
    env->stck = pvec_pop(env->stck, &list);
    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);		/* stack is saved in node */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &list);	/* take R from stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove X from old stack */
    node.u.lis = pvec_add(node.u.lis, list);	/* add R to old stack */
    pvec_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
