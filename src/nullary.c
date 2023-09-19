/*
    module  : nullary.c
    version : 1.11
    date    : 09/19/23
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
    list = lst_pop(env->stck);
    lst_init(node.u.lis);
    lst_copy(node.u.lis, env->stck);	/* stack is saved in node */
    exeterm(env, list.u.lis);
    list = lst_pop(env->stck);		/* take R from stack */
    lst_push(node.u.lis, list);		/* add R to old stack */
    lst_copy(env->stck, node.u.lis);	/* restore old stack with R on top */
}
#endif
