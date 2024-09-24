/*
    module  : condnestrec.c
    version : 1.17
    date    : 09/18/24
*/
#ifndef CONDNESTREC_C
#define CONDNESTREC_C

/**
OK  2750  condnestrec  :  DU  [ [C1] [C2] .. [D] ]  ->  ...
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

    for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = vec_at(aggr.u.lis, i);
	if (!i) {
	    j = vec_size(elem.u.lis) - 1;
	    break;
	}
	node = vec_back(elem.u.lis);
	exeterm(env, node.u.lis);
	node = vec_pop(env->stck);
	if (node.u.num) {
	    j = vec_size(elem.u.lis) - 2;
	    break;
	}
    }
    node = vec_at(elem.u.lis, j);
    exeterm(env, node.u.lis);
    for (i = j - 1; i >= 0; i--) {
	aux_condnestrec(env, aggr);
	node = vec_at(elem.u.lis, i);
	exeterm(env, node.u.lis);
    }
}

void condnestrec_(pEnv env)
{
    Node aggr;

    PARM(1, CASE);
    aggr = vec_pop(env->stck);
    aux_condnestrec(env, aggr);
}
#endif
