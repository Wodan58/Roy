/*
    module  : unary4.c
    version : 1.17
    date    : 09/19/23
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
    node[3] = lst_pop(env->stck);	/* W, expose Z */
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
    lst_push(env->stck, node[3]);	/* restore W */
    exeterm(env, list.u.lis);
    node[3] = lst_pop(env->stck);	/* W' */
    lst_push(env->stck, node[0]);	/* push X' */
    lst_push(env->stck, node[1]);	/* push Y' */
    lst_push(env->stck, node[2]);	/* push Z' */
    lst_push(env->stck, node[3]);	/* push W' */
}
#endif
