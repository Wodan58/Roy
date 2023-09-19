/*
    module  : tailrec.c
    version : 1.21
    date    : 09/19/23
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
OK 2720  tailrec  :  DDDU	[P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void aux_tailrec(pEnv env, NodeList *prog[3])
{
    Node node;

    for (;;) {
	exeterm(env, prog[0]);
	node = lst_pop(env->stck);
	if (node.u.num) {
	    exeterm(env, prog[1]);
	    break;
	}
	exeterm(env, prog[2]);
    }
}

void tailrec_(pEnv env)
{
    Node node;
    NodeList *prog[3];

    PARM(3, IFTE);
    node = lst_pop(env->stck);
    prog[2] = node.u.lis;
    node = lst_pop(env->stck);
    prog[1] = node.u.lis;
    node = lst_pop(env->stck);
    prog[0] = node.u.lis;
    aux_tailrec(env, prog);
}
#endif
