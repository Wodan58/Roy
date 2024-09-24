/*
    module  : cleave.c
    version : 1.20
    date    : 09/18/24
*/
#ifndef CLEAVE_C
#define CLEAVE_C

/**
OK  2580  cleave  :  DDDAA  X [P1] [P2]  ->  R1 R2
Executes P1 and P2, each with X on top, producing two results.
*/
void cleave_(pEnv env)
{					/* X [P1] [P2] cleave ==> X1 X2 */
    Node first, second, result[2];

    PARM(3, WHILE);
    second = vec_pop(env->stck);	/* P2 */
    first = vec_pop(env->stck);		/* P1 */
    result[1] = vec_back(env->stck);	/* copy X */
    exeterm(env, first.u.lis);		/* P1 */
    result[0] = vec_pop(env->stck);	/* first result */
    vec_push(env->stck, result[1]);	/* restore X */
    exeterm(env, second.u.lis);		/* P2 */
    result[1] = vec_pop(env->stck);	/* second result */
    vec_push(env->stck, result[0]);	/* push first */
    vec_push(env->stck, result[1]);	/* push second */
}
#endif
