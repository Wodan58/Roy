/*
    module  : treestep.c
    version : 1.18
    date    : 10/12/23
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
OK 2870  treestep  :  DDU	T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void aux_treestep(pEnv env, NodeList *list)
{
    int i;
    Node node;

    node = pvec_lst(env->stck);
    if (node.op != LIST_)
	exeterm(env, list);
    else {
	env->stck = pvec_pop(env->stck, &node);
	for (i = pvec_cnt(node.u.lis) - 1; i >= 0; i--) {
	    env->stck = pvec_add(env->stck, pvec_nth(node.u.lis, i));
	    treestep(env, list);
	}
    }
}

void treestep_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = pvec_pop(env->stck);
    aux_treestep(env, node.u.lis);
}
#endif
