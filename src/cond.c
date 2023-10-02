/*
    module  : cond.c
    version : 1.21
    date    : 10/02/23
*/
#ifndef COND_C
#define COND_C

/**
OK 2690  cond  :  DU	[..[[Bi] Ti]..[D]]  ->  ...
Tries each Bi. If that yields true, then executes Ti and exits.
If no Bi yields true, executes default D.
*/
void cond_(pEnv env)
{
    int i;
    Node aggr, elem, node;

    PARM(1, CASE);
    env->stck = pvec_pop(env->stck, &aggr);
    for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	elem = pvec_nth(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	node = pvec_lst(elem.u.lis);
	exeterm(env, node.u.lis);
	env->stck = pvec_pop(env->stck, &node);
	if (node.u.num) {
	    node.u.lis = pvec_init();
	    pvec_shallow_copy(node.u.lis, elem.u.lis);
	    node.u.lis = pvec_del(node.u.lis);
	    break;
	}
    }
    exeterm(env, node.u.lis);
}
#endif
