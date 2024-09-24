/*
    module  : step.c
    version : 1.18
    date    : 09/18/24
*/
#ifndef STEP_C
#define STEP_C

/**
OK  2770  step  :  DDU  A [P]  ->  ...
Sequentially putting members of aggregate A onto stack,
executes P for each member of A.
*/
void step_(pEnv env)
{
    int64_t i, j;
    char *volatile ptr;
    Node list, aggr, node;

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	    node = vec_at(aggr.u.lis, i);
	    vec_push(env->stck, node);
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
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (j = 1, i = 0; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		node.u.num = i;
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
	    }
	break;

    default:
	break;
    }
}
#endif
