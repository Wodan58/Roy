/*
    module  : step.c
    version : 1.17
    date    : 10/12/23
*/
#ifndef STEP_C
#define STEP_C

/**
OK 2770  step  :  DDU	A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_(pEnv env)
{
    int64_t i, j;
    char *volatile ptr;
    Node aggr, list, node;

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	for (i = pvec_cnt(aggr.u.lis) - 1; i >= 0; i--) {
	    node = pvec_nth(aggr.u.lis, i);
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	ptr = aggr.u.str;
	node.op = CHAR_;
	for (i = 0, j = strlen(ptr); i < j; i++) {
	    node.u.num = ptr[i];
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		node.u.num = i;
		env->stck = pvec_add(env->stck, node);
		exeterm(env, list.u.lis);
	    }
	break;

    default:
	break;
    }
}
#endif
