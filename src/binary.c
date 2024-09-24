/*
    module  : binary.c
    version : 1.12
    date    : 09/18/24
*/
#ifndef BINARY_C
#define BINARY_C

/**
OK  2560  binary  :  DDDA  X Y [P]  ->  R
Executes P, which leaves R on top of the stack.
No matter how many parameters this consumes,
exactly two are removed from the stack.
*/
void binary_(pEnv env)
{
    int size;
    Node list, node;

    PARM(3, DIP);
    list = vec_pop(env->stck);
    size = vec_size(env->stck) - 2;	/* remove X and Y */
    vec_copy_count(node.u.lis, env->stck, size);	/* save stack w/o X,Y */
    exeterm(env, list.u.lis);		/* execute program */
    list = vec_pop(env->stck);		/* take R from stack */
    vec_push(node.u.lis, list);		/* add R to old stack */
    vec_copy_count(env->stck, node.u.lis, size + 1);	/* restore stack w/ R */
}
#endif
