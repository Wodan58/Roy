/*
    module  : condnestrec.c
    version : 1.16
    date    : 10/02/23
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

/**
OK 2750  condnestrec  :  DU	[ [C1] [C2] .. [D] ]  ->  ...
A generalisation of condlinrec.
Each [Ci] is of the form [[B] [R1] [R2] .. [Rn]] and [D] is of the form
[[R1] [R2] .. [Rn]]. Tries each B, or if all fail, takes the default [D].
For the case taken, executes each [Ri] but recurses between any two
consecutive [Ri] (n > 3 would be exceptional.)
*/
void aux_condnestrec(pEnv env, Node aggr)
{
    int i, j = 0;
    Node elem, node;

    for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	elem = pvec_nth(aggr.u.lis, i);
	if (!i) {
	    j = pvec_cnt(elem.u.lis) - 1;
	    break;
	}
	node = pvec_lst(elem.u.lis);
	exeterm(env, node.u.lis);
	env->stck = pvec_pop(env->stck, &node);
	if (node.u.num) {
	    j = pvec_cnt(elem.u.lis) - 2;
	    break;
	}
    }
    node = pvec_nth(elem.u.lis, j);
    exeterm(env, node.u.lis);
    for (i = j - 1; i >= 0; i--) {
	aux_condnestrec(env, aggr);
	node = pvec_nth(elem.u.lis, i);
	exeterm(env, node.u.lis);
    }
}

void condnestrec_(pEnv env)
{
    Node aggr;

    PARM(1, CASE);
    env->stck = pvec_pop(env->stck, &aggr);
    aux_condnestrec(env, aggr);
}
#endif
