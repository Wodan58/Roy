/*
    module  : unary3.c
    version : 1.18
    date    : 10/02/23
*/
#ifndef UNARY3_C
#define UNARY3_C

/**
OK 2510  unary3  :  DDDDAAA	X1 X2 X3 [P]  ->  R1 R2 R3
Executes P three times, with Xi, returns Ri (i = 1..3).
*/
PRIVATE void unary3_(pEnv env)
{					/*  X Y Z [P]  unary3  ==>  X' Y' Z'  */
    PARM(4, DIP);
    Node list, node[3];

    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &node[2]);	/* Z, expose Y */
    env->stck = pvec_pop(env->stck, &node[1]);	/* Y, expose X */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[0]);	/* X' */
    env->stck = pvec_add(env->stck, node[1]);	/* restore Y */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[1]);	/* Y' */
    env->stck = pvec_add(env->stck, node[2]);	/* restore Z */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[2]);	/* Z' */
    env->stck = pvec_add(env->stck, node[0]);	/* push X' */
    env->stck = pvec_add(env->stck, node[1]);	/* push Y' */
    env->stck = pvec_add(env->stck, node[2]);	/* push Z' */
}
#endif
