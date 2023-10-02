/*
    module  : unary4.c
    version : 1.18
    date    : 10/02/23
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
OK 2520  unary4  :  DDDDDAAAA	X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
PRIVATE void unary4_(pEnv env)
{					/* X Y Z W [P] unary4 ==> X' Y' Z' W' */
    PARM(5, DIP);
    Node list, node[4];

    list = lst_pop(env->stck);
    env->stck = pvec_pop(env->stck, &node[3]);	/* W, expose Z */
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
    env->stck = pvec_add(env->stck, node[3]);	/* restore W */
    exeterm(env, list.u.lis);
    env->stck = pvec_pop(env->stck, &node[3]);	/* W' */
    env->stck = pvec_add(env->stck, node[0]);	/* push X' */
    env->stck = pvec_add(env->stck, node[1]);	/* push Y' */
    env->stck = pvec_add(env->stck, node[2]);	/* push Z' */
    env->stck = pvec_add(env->stck, node[3]);	/* push W' */
}
#endif
