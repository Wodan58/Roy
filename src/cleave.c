/*
    module  : cleave.c
    version : 1.18
    date    : 09/19/23
*/
#ifndef CLEAVE_C
#define CLEAVE_C

/**
OK 2580  cleave  :  DDDAA	X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
PRIVATE void cleave_(pEnv env)
{					/* X [P1] [P2] cleave ==> X1 X2 */
    Node first, second, result[2];

    PARM(3, WHILE);
    second = lst_pop(env->stck);	/* P2 */
    first = lst_pop(env->stck);		/* P1 */
    result[1] = lst_back(env->stck);	/* copy X */
    exeterm(env, first.u.lis);		/* P1 */
    result[0] = lst_pop(env->stck);	/* first result */
    lst_push(env->stck, result[1]);	/* restore X */
    exeterm(env, second.u.lis);		/* P2 */
    result[1] = lst_pop(env->stck);	/* second result */
    lst_push(env->stck, result[0]);	/* push first */
    lst_push(env->stck, result[1]);	/* push second */
}
#endif
