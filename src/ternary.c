/*
    module  : ternary.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef TERNARY_C
#define TERNARY_C

/**
OK  2570  ternary  :  DDDDA  X Y Z [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly three are removed from the stack.
*/
void ternary_(pEnv env)
{
    int size;
    Node list, node;

    PARM(4, DIP);
    list = vec_pop(env->stck);
    size = vec_size(env->stck) - 3;			/* remove X, Y, and Z */
    vec_copy_count(node.u.lis, env->stck, size);	/* save stack - X,Y,Z */
    exeterm(env, list.u.lis);
    list = vec_pop(env->stck);				/* take R from stack */
    vec_push(node.u.lis, list);				/* add R to old stack */
    vec_copy_count(env->stck, node.u.lis, size + 1);	/* restore old stack */
}
#endif
