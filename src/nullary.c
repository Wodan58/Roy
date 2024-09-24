/*
    module  : nullary.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef NULLARY_C
#define NULLARY_C

/**
OK  2480  nullary  :  DA  [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes, none are removed from the stack.
*/
void nullary_(pEnv env)
{
    int size;
    Node list, node;

    PARM(1, DIP);
    list = vec_pop(env->stck);
    size = vec_size(env->stck);
    vec_copy_count(node.u.lis, env->stck, size);	/* save stack */
    exeterm(env, list.u.lis);
    list = vec_pop(env->stck);		/* take R from stack */
    vec_push(node.u.lis, list);		/* add R to old stack */
    vec_copy_count(env->stck, node.u.lis, size + 1);	/* restore old stack */
}
#endif
