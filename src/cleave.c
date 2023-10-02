/*
    module  : cleave.c
    version : 1.19
    date    : 10/02/23
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
    env->stck = pvec_pop(env->stck, &second);		/* P2 */
    env->stck = pvec_pop(env->stck, &first);		/* P1 */
    result[1] = pvec_lst(env->stck);			/* copy X */
    exeterm(env, first.u.lis);				/* P1 */
    env->stck = pvec_pop(env->stck, &result[0]);	/* first result */
    env->stck = pvec_add(env->stck, result[1]);		/* restore X */
    exeterm(env, second.u.lis);				/* P2 */
    env->stck = pvec_pop(env->stck, &result[1]);	/* second result */
    env->stck = pvec_add(env->stck, result[0]);		/* push first */
    env->stck = pvec_add(env->stck, result[1]);		/* push second */
}
#endif
