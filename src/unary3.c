/*
    module  : unary3.c
    version : 1.17
    date    : 09/19/23
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

    list = lst_pop(env->stck);
    node[2] = lst_pop(env->stck);	/* Z, expose Y */
    node[1] = lst_pop(env->stck);	/* Y, expose X */
    exeterm(env, list.u.lis);
    node[0] = lst_pop(env->stck);	/* X' */
    lst_push(env->stck, node[1]);	/* restore Y */
    exeterm(env, list.u.lis);
    node[1] = lst_pop(env->stck);	/* Y' */
    lst_push(env->stck, node[2]);	/* restore Z */
    exeterm(env, list.u.lis);
    node[2] = lst_pop(env->stck);	/* Z' */
    lst_push(env->stck, node[0]);	/* push X' */
    lst_push(env->stck, node[1]);	/* push Y' */
    lst_push(env->stck, node[2]);	/* push Z' */
}
#endif
