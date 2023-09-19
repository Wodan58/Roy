/*
    module  : unary2.c
    version : 1.20
    date    : 09/19/23
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
    list = lst_pop(env->stck);
    node[1] = lst_pop(env->stck);	/* Z, expose Y */
    exeterm(env, list.u.lis);
    node[0] = lst_pop(env->stck);	/* Y' */
    lst_push(env->stck, node[1]);	/* restore Z */
    exeterm(env, list.u.lis);
    node[1] = lst_pop(env->stck);	/* Z' */
    lst_push(env->stck, node[0]);	/* push Y' */
    lst_push(env->stck, node[1]);	/* push Z' */
}
#endif
