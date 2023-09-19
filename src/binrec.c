/*
    module  : binrec.c
    version : 1.20
    date    : 09/19/23
*/
#ifndef BINREC_C
#define BINREC_C

/**
OK 2730  binrec  :  DDDDU	[P] [T] [R1] [R2]  ->  ...
Executes P. If that yields true, executes T.
Else uses R1 to produce two intermediates, recurses on both,
then executes R2 to combine their results.
*/
void binrec(pEnv env, NodeList *prog[4])
{
    Node node;

    exeterm(env, prog[0]);
    node = lst_pop(env->stck);
    if (node.u.num)
	exeterm(env, prog[1]);
    else {
	exeterm(env, prog[2]);
	node = lst_pop(env->stck);
	binrec(env, prog);
	lst_push(env->stck, node);
	binrec(env, prog);
	exeterm(env, prog[3]);
    }
}

void binrec_(pEnv env)
{
    Node node;
    NodeList *prog[4];

    PARM(4, LINREC);
    node = lst_pop(env->stck);
    prog[3] = node.u.lis;
    node = lst_pop(env->stck);
    prog[2] = node.u.lis;
    node = lst_pop(env->stck);
    prog[1] = node.u.lis;
    node = lst_pop(env->stck);
    prog[0] = node.u.lis;
    binrec(env, prog);
}
#endif
