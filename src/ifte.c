/*
    module  : ifte.c
    version : 1.23
    date    : 10/02/23
*/
#ifndef IFTE_C
#define IFTE_C

/**
OK 2600  ifte  :  DDDP	[B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
void ifte_(pEnv env)
{
    Node first, second, third;

    PARM(3, IFTE);
    env->stck = pvec_pop(env->stck, &third);
    env->stck = pvec_pop(env->stck, &second);
    env->stck = pvec_pop(env->stck, &first);
    /*
	execute the test of the ifte
    */
    exeterm(env, first.u.lis);
    /*
	pop the result from the stack
    */
    env->stck = pvec_pop(env->stck, &first);
    if (first.u.num)
	exeterm(env, second.u.lis);
    else
	exeterm(env, third.u.lis);
}
#endif
