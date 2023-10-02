/*
    module  : linrec.c
    version : 1.21
    date    : 10/02/23
*/
#ifndef LINREC_C
#define LINREC_C

/**
OK 2710  linrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses, executes R2.
*/
void linrec(pEnv env, NodeList *prog[4])
{
    Node node;

    exeterm(env, prog[0]);
    env->stck = pvec_pop(env->stck, &node);
    if (node.u.num)
	exeterm(env, prog[1]);
    else {
	exeterm(env, prog[2]);
	linrec(env, prog);
	exeterm(env, prog[3]);
    }
}

void linrec_(pEnv env)
{
    Node node;
    NodeList *prog[4];

    PARM(4, LINREC);
    env->stck = pvec_pop(env->stck, &node);
    prog[3] = node.u.lis;
    env->stck = pvec_pop(env->stck, &node);
    prog[2] = node.u.lis;
    env->stck = pvec_pop(env->stck, &node);
    prog[1] = node.u.lis;
    env->stck = pvec_pop(env->stck, &node);
    prog[0] = node.u.lis;
    linrec(env, prog);
}
#endif
