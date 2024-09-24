/*
    module  : treestep.c
    version : 1.19
    date    : 09/18/24
*/
#ifndef TREESTEP_C
#define TREESTEP_C

/**
OK  2870  treestep  :  DDU  T [P]  ->  ...
Recursively traverses leaves of tree T, executes P for each leaf.
*/
void aux_treestep(pEnv env, NodeList list)
{
    int i;
    Node node;

    node = vec_back(env->stck);
    if (node.op != LIST_)
	exeterm(env, list);
    else {
	node = vec_pop(env->stck);
	for (i = vec_size(node.u.lis) - 1; i >= 0; i--) {
	    vec_push(env->stck, vec_at(node.u.lis, i));
	    treestep(env, list);
	}
    }
}

void treestep_(pEnv env)
{
    Node node;

    PARM(2, DIP);
    node = vec_pop(env->stck);
    aux_treestep(env, node.u.lis);
}
#endif
