/*
    module  : treestep.c
    version : 1.16
    date    : 09/19/23
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
    Node node, temp;

    node = lst_back(env->stck);
    if (node.op != LIST_)
	exeterm(env, list);
    else {
	node = lst_pop(env->stck);
	for (i = lst_size(node.u.lis) - 1; i >= 0; i--) {
	    temp = lst_at(node.u.lis, i);
	    lst_push(env->stck, temp);
	    aux_treestep(env, list);
	}
    }
}

void treestep_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = lst_pop(env->stck);
    aux_treestep(env, node.u.lis);
}
#endif
