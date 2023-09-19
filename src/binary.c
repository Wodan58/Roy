/*
    module  : binary.c
    version : 1.10
    date    : 09/19/23
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
    list = lst_pop(env->stck);
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);	/* stack is saved in node */
    exeterm(env, list.u.lis);
    list = lst_pop(env->stck);		/* take R from stack */
    (void)lst_pop(node.u.lis);		/* remove Y from old stack */
    (void)lst_pop(node.u.lis);		/* remove X from old stack */
    lst_push(node.u.lis, list);		/* add R to old stack */
    lst_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
