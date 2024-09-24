/*
    module  : unary4.c
    version : 1.20
    date    : 09/18/24
*/
#ifndef UNARY4_C
#define UNARY4_C

/**
OK  2520  unary4  :  DDDDDAAAA  X1 X2 X3 X4 [P]  ->  R1 R2 R3 R4
Executes P four times, with Xi, returns Ri (i = 1..4).
*/
void unary4_(pEnv env)
{					/* X Y Z W [P] unary4 ==> X' Y' Z' W' */
    PARM(5, DIP);
    Node list, node[4];

    list = vec_pop(env->stck);
    node[3] = vec_pop(env->stck);	/* W, expose Z */
    node[2] = vec_pop(env->stck);	/* Z, expose Y */
    node[1] = vec_pop(env->stck);	/* Y, expose X */
    exeterm(env, list.u.lis);
    node[0] = vec_pop(env->stck);	/* X' */
    vec_push(env->stck, node[1]);	/* restore Y */
    exeterm(env, list.u.lis);
    node[1] = vec_pop(env->stck);	/* Y' */
    vec_push(env->stck, node[2]);	/* restore Z */
    exeterm(env, list.u.lis);
    node[2] = vec_pop(env->stck);	/* Z' */
    vec_push(env->stck, node[3]);	/* restore W */
    exeterm(env, list.u.lis);
    node[3] = vec_pop(env->stck);	/* W' */
    vec_push(env->stck, node[0]);	/* push X' */
    vec_push(env->stck, node[1]);	/* push Y' */
    vec_push(env->stck, node[2]);	/* push Z' */
    vec_push(env->stck, node[3]);	/* push W' */
}
#endif
