/*
    module  : condnestrec.c
    version : 1.15
    date    : 09/19/23
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

    for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = lst_at(aggr.u.lis, i);
	if (!i) {
	    j = lst_size(elem.u.lis) - 1;
	    break;
	}
	node = lst_back(elem.u.lis);
	exeterm(env, node.u.lis);
	node = lst_pop(env->stck);
	if (node.u.num) {
	    j = lst_size(elem.u.lis) - 2;
	    break;
	}
    }
    node = lst_at(elem.u.lis, j);
    exeterm(env, node.u.lis);
    for (i = j - 1; i >= 0; i--) {
	aux_condnestrec(env, aggr);
	node = lst_at(elem.u.lis, i);
	exeterm(env, node.u.lis);
    }
}

void condnestrec_(pEnv env)
{
    Node aggr;

    PARM(1, CASE);
    aggr = lst_pop(env->stck);
    aux_condnestrec(env, aggr);
}
#endif
