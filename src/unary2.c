/*
    module  : unary2.c
    version : 1.21
    date    : 10/02/23
*/
#ifndef UNARY2_C
#define UNARY2_C

/**
OK 2500  unary2  :  DDDAA	X1 X2 [P]  ->  R1 R2
Executes P twice, with X1 and X2 on top of the stack.
Returns the two values R1 and R2.
*/
void unary2_(pEnv env)
{					/*  Y  Z  [P]  unary2  ==>  Y'  Z'  */
    Node list, node[2];

    PARM(3, DIP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node[1]);	/* Z, expose Y */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[0]);	/* Y' */
    env->stck = pvec_add(env->stck, node[1]);	/* restore Z */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[1]);	/* Z' */
    env->stck = pvec_add(env->stck, node[0]);	/* push Y' */
    env->stck = pvec_add(env->stck, node[1]);	/* push Z' */
}
#endif
