/*
    module  : step.c
    version : 1.15
    date    : 09/19/23
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
    Node aggr, list, node;

    PARM(2, STEP);
    list = lst_pop(env->stck);
    aggr = lst_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	    node = lst_at(aggr.u.lis, i);
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    node.u.num = aggr.u.str[i];
	    lst_push(env->stck, node);
	    exeterm(env, list.u.lis);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		node.u.num = i;
		lst_push(env->stck, node);
		exeterm(env, list.u.lis);
	    }
	break;

    default:
	break;
    }
}
#endif
