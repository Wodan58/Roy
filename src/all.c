/*
    module  : all.c
    version : 1.14
    date    : 09/18/24
*/
#ifndef ALL_C
#define ALL_C

/**
OK  2860  all  :  DDA  A [B]  ->  X
Applies test B to members of aggregate A, X = true if all pass.
*/
void all_(pEnv env)
{
    Node list, aggr, node;
    int64_t i, j, result = 1;	/* assume true */

    PARM(2, STEP);
    list = vec_pop(env->stck);
    aggr = vec_pop(env->stck);
    switch (aggr.op) {
    case LIST_:
	for (i = vec_size(aggr.u.lis) - 1; i >= 0; i--) {
	    /*
		push the element to be tested
	    */
	    node = vec_at(aggr.u.lis, i);
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
	    if (result != node.u.num) {
		result = 0;
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
	    vec_push(env->stck, node);
	    exeterm(env, list.u.lis);
	    node = vec_pop(env->stck);
	    if (result != node.u.num) {
		result = 0;
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
		vec_push(env->stck, node);
		exeterm(env, list.u.lis);
		node = vec_pop(env->stck);
		if (result != node.u.num) {
		    result = 0;
		    break;
		}
	    }
	break;

    default:
	break;
    }
    node.u.num = result;
    node.op = BOOLEAN_;
    vec_push(env->stck, node);
}
#endif
