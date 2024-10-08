/*
    module  : case.c
    version : 1.22
    date    : 09/18/24
*/
#ifndef CASE_C
#define CASE_C

#include "compare.h"

/**
OK  2100  case  :  DDU  X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
void case_(pEnv env)
{
    int i;
    Node aggr, node, elem;

    PARM(2, CASE);
    aggr = vec_pop(env->stck);
    node = vec_back(env->stck);
    for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	elem = vec_at(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	if (!Compare(env, node, vec_back(elem.u.lis))) {
	    vec_shallow_copy(node.u.lis, elem.u.lis);
	    (void)vec_pop(node.u.lis);
	    (void)vec_pop(env->stck);
	    break;
	}
    }
    exeterm(env, node.u.lis);
}
#endif
