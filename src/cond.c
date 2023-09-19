/*
    module  : cond.c
    version : 1.20
    date    : 09/19/23
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
    Node aggr, quot, test, node;

    PARM(1, CASE);
    aggr = lst_pop(env->stck);
    for (i = lst_size(aggr.u.lis) - 1; i >= 0; i--) {
	quot = lst_at(aggr.u.lis, i);
	if (!i) {
	    node = quot;
	    break;
	}
	test = lst_back(quot.u.lis);
	exeterm(env, test.u.lis);
	node = lst_pop(env->stck);
	if (node.u.num) {
	    lst_init(node.u.lis);
	    lst_shallow_copy(node.u.lis, quot.u.lis);
	    (void)lst_pop(node.u.lis);
	    break;
	}
    }
    exeterm(env, node.u.lis);
}
#endif
