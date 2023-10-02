/*
    module  : nullary.c
    version : 1.12
    date    : 10/02/23
*/
#ifndef NULLARY_C
#define NULLARY_C

/**
OK 2480  nullary  :  DA	[P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
void nullary_(pEnv env)
{
    Node list, node;

    PARM(1, DIP);
    env->stck = pvec_pop(env->stck, &list);
    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);		/* stack is saved in node */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &list);	/* take R from stack */
    node.u.lis = pvec_add(node.u.lis, list);	/* add R to old stack */
    lst_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
