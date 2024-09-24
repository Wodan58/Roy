/*
    module  : ifte.c
    version : 1.24
    date    : 09/18/24
*/
#ifndef IFTE_C
#define IFTE_C

/**
OK  2600  ifte  :  DDDP  [B] [T] [F]  ->  ...
Executes B. If that yields true, then executes T else executes F.
*/
void ifte_(pEnv env)
{
    Node first, second, third;

    PARM(3, IFTE);
    third = vec_pop(env->stck);
    second = vec_pop(env->stck);
    first = vec_pop(env->stck);
    /*
	execute the test of the ifte
    */
    exeterm(env, first.u.lis);
    /*
	pop the result from the stack
    */
    first = vec_pop(env->stck);
    if (first.u.num)
	exeterm(env, second.u.lis);
    else
	exeterm(env, third.u.lis);
}
#endif
