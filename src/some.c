/*
    module  : some.c
    version : 1.13
    date    : 10/02/23
*/
#ifndef SOME_C
#define SOME_C

/**
OK 2850  some  :  DDA	A [B]  ->  X
Applies test B to members of aggregate A, X = true if some pass.
*/
void some_(pEnv env)
{
    Node aggr, list, node;
    int64_t i, j, result = 0;	/* assume false */

    PARM(2, STEP);
    env->stck = pvec_pop(env->stck, &list);
    env->stck = pvec_pop(env->stck, &aggr);
    switch (aggr.op) {
    case LIST_:
	for (i = 0, j = pvec_cnt(aggr.u.lis); i < j; i++) {
	    /*
		push the element to be tested
	    */
	    node = pvec_nth(aggr.u.lis, i);
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &node);
	    if (node.u.num) {
		result = 1;
		break;
	    }
	}
	break;

    case STRING_:
    case BIGNUM_:
    case USR_STRING_:
	node.op = CHAR_;
	for (i = 0, j = strlen(aggr.u.str); i < j; i++) {
	    /*
		push the element to be tested
	    */
	    node.u.num = aggr.u.str[i];
	    env->stck = pvec_add(env->stck, node);
	    exeterm(env, list.u.lis);
	    env->stck = pvec_pop(env->stck, &node);
	    if (node.u.num) {
		result = 1;
		break;
	    }
	}
	break;

    case SET_:
	node.op = INTEGER_;
	for (i = 0, j = 1; i < SETSIZE; i++, j <<= 1)
	    if (aggr.u.set & j) {
		/*
		    push the element to be tested
		*/
		node.u.num = i;
		env->stck = pvec_add(env->stck, node);
		exeterm(env, list.u.lis);
		env->stck = pvec_pop(env->stck, &node);
		if (node.u.num) {
		    result = 1;
		    break;
		}
	    }
	break;

    default:
	break;
    }
    node.u.num = result;
    node.op = BOOLEAN_;
    env->stck = pvec_add(env->stck, node);
}
#endif
