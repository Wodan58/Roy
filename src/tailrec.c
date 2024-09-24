/*
    module  : tailrec.c
    version : 1.23
    date    : 09/18/24
*/
#ifndef TAILREC_C
#define TAILREC_C

/**
OK  2720  tailrec  :  DDDU  [P] [T] [R1]  ->  ...
Executes P. If that yields true, executes T.
Else executes R1, recurses.
*/
void tailrec(pEnv env, NodeList prog[3])
{
    Node node;

    for (;;) {
	exeterm(env, prog[0]);
	node = vec_pop(env->stck);
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
    NodeList prog[3];

    PARM(3, IFTE);
    node = vec_pop(env->stck);
    prog[2] = node.u.lis;
    node = vec_pop(env->stck);
    prog[1] = node.u.lis;
    node = vec_pop(env->stck);
    prog[0] = node.u.lis;
    tailrec(env, prog);
}
#endif
