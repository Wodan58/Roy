/*
    module  : ternary.c
    version : 1.11
    date    : 10/02/23
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
OK 2570  ternary  :  DDDDA 	X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void ternary_(pEnv env)
{
    Node node, list;

    PARM(4, DIP);
    env->stck = pvec_pop(env->stck, &list);
    node.u.lis = pvec_init();
    pvec_copy(node.u.lis, env->stck);		/* stack is saved in node */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &list);	/* take R from stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove Z from old stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove Y from old stack */
    node.u.lis = pvec_pop(node.u.lis);		/* remove X from old stack */
    node.u.lis = pvec_add(node.u.lis, list);	/* add R to old stack */
    pvec_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
