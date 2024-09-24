/*
    module  : unary.c
    version : 1.13
    date    : 09/18/24
*/
#ifndef UNARY_C
#define UNARY_C

/**
OK  2490  unary  :  DDA  X [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly one is removed from the stack.
*/
void unary_(pEnv env)
{
    int size;
    Node list, node;

    PARM(2, DIP);
    list = vec_pop(env->stck);
    size = vec_size(env->stck) - 1;			/* remove X */
    vec_copy_count(node.u.lis, env->stck, size);	/* save old stack */
    exeterm(env, list.u.lis);
    list = vec_pop(env->stck);				/* take R from stack */
    vec_push(node.u.lis, list);				/* add R to old stack */
    vec_copy_count(env->stck, node.u.lis, size + 1);	/* restore old stack */
}
#endif
