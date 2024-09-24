/*
    module  : unary2.c
    version : 1.22
    date    : 09/18/24
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
OK  2500  unary2  :  DDDAA  X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void unary2_(pEnv env)
{					/*  Y  Z  [P]  unary2  ==>  Y'  Z'  */
    Node list, node[2];

    PARM(3, DIP);
    list = vec_pop(env->stck);
    node[1] = vec_pop(env->stck);	/* Z, expose Y */
    exeterm(env, list.u.lis);
    node[0] = vec_pop(env->stck);	/* Y' */
    vec_push(env->stck, node[1]);	/* restore Z */
    exeterm(env, list.u.lis);
    node[1] = vec_pop(env->stck);	/* Z' */
    vec_push(env->stck, node[0]);	/* push Y' */
    vec_push(env->stck, node[1]);	/* push Z' */
}
#endif
