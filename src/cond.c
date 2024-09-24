/*
    module  : cond.c
    version : 1.22
    date    : 09/18/24
*/
#ifndef COND_C
#define COND_C

/**
OK  2690  cond  :  DU  [..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void cond_(pEnv env)
{
    int i;
    Node aggr, elem, node;

    PARM(1, CASE);
    aggr = vec_pop(env->stck);
    for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = vec_at(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	node = vec_back(elem.u.lis);
	exeterm(env, node.u.lis);
	node = vec_pop(env->stck);
	if (node.u.num) {
	    vec_shallow_copy(node.u.lis, elem.u.lis);
	    (void)vec_pop(node.u.lis);
	    break;
	}
    }
    exeterm(env, node.u.lis);
}
#endif
