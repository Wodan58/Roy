/*
    module  : case.c
    version : 1.21
    date    : 10/02/23
*/
#ifndef CASE_C
#define CASE_C

#include "compare.h"

/**
OK 2100  case  :  DDU	X [..[X Y]..]  ->  Y i
Indexing on the value of X, execute the matching Y.
*/
void case_(pEnv env)
{
    int i;
    Node node, aggr, elem;

    PARM(2, CASE);
    env->stck = pvec_pop(env->stck, &aggr);
    node = pvec_lst(env->stck);
    for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	elem = pvec_nth(aggr.u.lis, i);
	if (!i) {
	    node = elem;
	    break;
	}
	if (!Compare(env, node, pvec_lst(elem.u.lis))) {
	    node.u.lis = pvec_init();
	    pvec_shallow_copy(node.u.lis, elem.u.lis);
	    node.u.lis = pvec_del(node.u.lis);
	    env->stck = pvec_del(env->stck);
	    break;
	}
    }
    exeterm(env, node.u.lis);
}
#endif
