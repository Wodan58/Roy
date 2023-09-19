/*
    module  : unary.c
    version : 1.11
    date    : 09/19/23
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
    list = lst_pop(env->stck);
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);	/* stack is saved in node */
    exeterm(env, list.u.lis);
    list = lst_pop(env->stck);		/* take R from stack */
    (void)lst_pop(node.u.lis);		/* remove X from old stack */
    lst_push(node.u.lis, list);		/* add R to old stack */
    lst_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
